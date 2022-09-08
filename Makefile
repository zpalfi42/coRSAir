# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 12:16:53 by zpalfi            #+#    #+#              #
#    Updated: 2022/08/03 12:49:00 by zpalfi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= coRSAir

#--------------- DIRS ---------------#

INCLUDE_DIR	= include
SRC_DIR		= src
LIBS_DIR	= libs
OBJS_DIR	= objs

#--------------- FILES ---------------#

LIBS			= $(LIBS_DIR)/Libft/libft.a \
			  		$(LIBS_DIR)/Get_Next_Line/get_next_line.a \

LIBS_HEADERS	= -I $(LIBS_DIR)/Libft/include/ \
				  -I $(LIBS_DIR)/Get_Next_Line/include/ \

INC				= -I $(INCLUDE_DIR) $(LIBS_HEADERS)

SRC				= coRSAir.c \

OBJ				= $(addprefix $(OBJS_DIR)/,$(SRC:.c=.o))

CPPFLAGS		= -I/System/Volumes/Data/sgoinfre/Perso/zpalfi/homebrew/opt/openssl@3/include
LDFLAGS			= /System/Volumes/Data/sgoinfre/Perso/zpalfi/homebrew/opt/openssl@3/lib/libcrypto.a

#--------------- COMPILATION ---------------#

CC			= gcc
CFLAGS		= -g $(INC)

#--------------- RULES ---------------#

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) -c $(CFLAGS) -o $@ $^
	@echo "Compiling $^"

all:	$(NAME)

$(NAME): $(OBJ) $(LIBS)
	@$(CC) $(OBJ) $(LIBS) $(LDFLAGS) -o $(NAME)
	@echo "Built $(NAME)"

$(LIBS_DIR)/Libft/libft.a:
	@make -C $(LIBS_DIR)/Libft

$(LIBS_DIR)/Get_Next_Line/get_next_line.a:
	@make -C $(LIBS_DIR)/Get_Next_Line

clean:
	@rm -rf $(OBJS_DIR)

fclean:	clean
	@make fclean -C $(LIBS_DIR)/Libft
	@make fclean -C $(LIBS_DIR)/Get_Next_Line
	@rm -f $(NAME)

re:	fclean all

.PHONY: all re clean fclean
