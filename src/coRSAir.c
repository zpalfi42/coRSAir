#include "libft.h"
#include "get_next_line.h"
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/bn.h>

RSA*	get_privkey(RSA	*pubkey, BIGNUM *paux)
{
	BIGNUM	*npriv;
	BIGNUM	*epriv;
	BIGNUM	*p;
	RSA		*privkey= RSA_new();
	BIGNUM	*q = BN_new();
	BIGNUM	*d = BN_new();
	BIGNUM	*p1 = BN_new();
	BIGNUM	*q1 = BN_new();
	BIGNUM	*dmp = BN_new();
	BIGNUM	*dmq = BN_new();
	BIGNUM	*iqmp = BN_new();
	BIGNUM	*phi = BN_new();
	BN_CTX	*ctx = BN_CTX_new();
	char	s1[100];
	char	s2[100];

	p = BN_dup(paux);
	npriv = BN_dup(RSA_get0_n(pubkey));
	epriv = BN_dup(RSA_get0_e(pubkey));
	BN_div(q, NULL, npriv, p, ctx);
	BN_sub(p1, p, BN_value_one());
	BN_sub(q1, q, BN_value_one());
	BN_mul(phi, p1, q1, ctx);
	BN_mod_inverse(d, epriv, phi, ctx);
	BN_mod(dmp, d, p1, ctx);
	BN_mod(dmq, d, q1, ctx);
	BN_mod_inverse(iqmp, q, p, ctx);
	RSA_set0_key(privkey, npriv, epriv, d);
	RSA_set0_factors(privkey, p, q);
	RSA_set0_crt_params(privkey, dmp, dmq, iqmp);
	if (RSA_check_key(privkey) != 1)
	{
		printf("\nOpenSSL reports internal inconsistency in generated RSA key!\n");
		exit(1);
	}
	printf("\nDo you want to see the full info of the private key? [y/n]: ");
	scanf("%s", s1);
	if (s1[0] == 'y' && s1[1] == '\0')
	{
		RSA_print_fp (stdout, privkey, 5);
		printf("\n");
		PEM_write_RSAPrivateKey (stdout, privkey, NULL, NULL, 0, 0, NULL);
	}
	else if (s1[0] == 'n' && s2[1] == '\0')
	{
		printf("\nDo you want to see only the private key? [y/n]: ");
		scanf("%s", s2);
		if (s2[0] == 'y')
		{
			PEM_write_RSAPrivateKey (stdout, privkey, NULL, NULL, 0, 0, NULL);
		}
	}
	BN_clear_free(phi);
	BN_clear_free(p1);
	BN_clear_free(q1);
	BN_CTX_free(ctx);
	return (privkey);
}

void	decrypt(char **argv, int i, RSA* privkey)
{
	unsigned char	*out;
	unsigned char	*in;
	size_t			inlen;
	char			*file;
	char			c;
	int				fd;
	int				z;
	int				x;

	file = malloc(sizeof(char) * (strlen(argv[i + 1]) + 1));
	z = 0;
	while (z < strlen(argv[i + 1]) - 3)
	{
		file[z] = argv[i + 1][z];
		z++;
	}
	file[z++] = 'b';
	file[z++] = 'i';
	file[z++] = 'n';
	file[z] = '\0';
	inlen = 0;
	fd = open(file, O_RDONLY);
	if (!fd)
		exit(1);
	while (read(fd, &c, 1))
		inlen++;
	close(fd);
	in = (unsigned char *)malloc(sizeof(unsigned char) * (inlen));
	fd = open(file, O_RDONLY);
	if (read(fd, in, inlen) < 0)
		exit(1);
	close(fd);
	out = malloc(RSA_size(privkey));
	RSA_private_decrypt(RSA_size(privkey), in, out, privkey, RSA_PKCS1_PADDING);
	x = 0;
	while (out[x] != '\n' && out[x] != '\0')
		x++;
	write(1, "\nEncrypted message: \n", 21);
	write(1, in, inlen);
	write(1, "\n\nDecrypted message: \n", 22);
	write(1, out, x);
	write(1, "\n\n", 2);
	free(file);
	free(in);
	free(out);
}

void	build_and_decrypt(int argc, char **argv, int i, int j, RSA** pubkey, BIGNUM *p)
{
	RSA*	privkey[2];
	char	s1[100];
	
	privkey[0] = get_privkey(pubkey[i], p);
	privkey[1] = get_privkey(pubkey[j], p);
	printf("\nDo you want to decrypt %.*sbin && %.*sbin? [y/n]: ", strlen(argv[i + 1]) - 3, argv[i + 1], strlen(argv[j + 1]) - 3, argv[j + 1]);
	scanf("%s", s1);
	if (s1[0] == 'y' && s1[1] == '\0')
	{
		decrypt(argv, i, privkey[0]);
		decrypt(argv, j, privkey[1]);
	}
	RSA_free(privkey[0]);
	RSA_free(privkey[1]);
}

int main(int argc, char **argv)
{
	if (argc == 2 && ft_strnstr(argv[1], ".crt", 100) != NULL)
	{
		BIO* certbio = BIO_new(BIO_s_file());
		BIO* outbio = BIO_new_fp(stdout, BIO_NOCLOSE);
		X509* cert = NULL;
		EVP_PKEY* key;
		RSA* pubkey = NULL;
		char	*n;
		char	*e;

		BIO_read_filename(certbio, argv[1]);
		if (!(cert = PEM_read_bio_X509(certbio, NULL, NULL, NULL)))
		{
			BIO_printf(outbio, "Error loading cert into memory\n");
			exit(-1);
		}
		key = X509_get_pubkey(cert);
		if (!(pubkey = EVP_PKEY_get1_RSA(key)))
		{
			printf("Couldn't convert to a RSA style key.\n");
			return (1);
		}
		n = BN_bn2dec(RSA_get0_n(pubkey));
		e = BN_bn2dec(RSA_get0_e(pubkey));
		printf("\nMODULUS:	%s\n\nEXPONENT:	%s\n\n", n, e);
		free(n);
		free(e);
		BIO_free_all(certbio);
		BIO_free_all(outbio);
		X509_free(cert);
		EVP_PKEY_free(key);
		RSA_free(pubkey);
	}
	else if (argc > 2 && ft_strnstr(argv[1], ".pem", 100) != NULL)
	{
		BIO				*certbio[argc];
		BIO				*outbio = BIO_new_fp(stdout, BIO_NOCLOSE);
		EVP_PKEY		*key[argc];
		RSA				*pubkey[argc];
		BN_CTX			*ctx;
		const BIGNUM	*n1;
		const BIGNUM	*n2;
		char			*bn;
		BIGNUM			*gcd;

		for (int i = 0; i < argc - 1; i++)
		{
			certbio[i] = BIO_new(BIO_s_file());
			key[i] = NULL;
			pubkey[i] = NULL;
			BIO_read_filename(certbio[i], argv[i + 1]);
			if (!(key[i] = PEM_read_bio_PUBKEY(certbio[i], NULL, NULL, NULL)))
			{
				BIO_printf(outbio, "Error loading key into memory\n");
				exit(-1);
			}
			if (!(pubkey[i] = EVP_PKEY_get1_RSA(key[i])))
			{
				printf("Couldn't convert to a RSA style key.\n");
				return (1);
			}
			EVP_PKEY_free(key[i]);
		}
		for (int i = 0; i < argc - 1; i++)
		{
			n1 = BN_dup(RSA_get0_n(pubkey[i]));
			for (int j = i + 1; j < argc - 1; j++)
			{
				n2 = BN_dup(RSA_get0_n(pubkey[j]));
				ctx = BN_CTX_new();
				gcd = BN_new();
				BN_gcd(gcd, n1, n2, ctx);
				bn = BN_bn2dec(gcd);
				if (strncmp(bn, "1\0", 2) != 0)
					build_and_decrypt(argc, argv, i, j, pubkey, gcd);
				BN_clear_free(gcd);
				BN_clear_free(n2);
				BN_CTX_free(ctx);
				free(bn);
			}
			BN_clear_free(n1);
		}
		for (int i = 0; i < argc - 1; i++)
		{
			RSA_free(pubkey[i]);
			BIO_free_all(certbio[i]);
		}
		BIO_free_all(outbio);
	}
	else
		printf("Usage:\nMode 1: ./corsair example.crt\nMode 2: ./corsair '.pem files'\n");
    return (0);
}