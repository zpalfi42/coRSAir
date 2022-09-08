# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/25 16:53:06 by zpalfi            #+#    #+#              #
#    Updated: 2022/03/14 13:55:06 by zpalfi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_printf
OUTPUT		= $(NAME).a

#--------------- DIRS ---------------#

INCLUDE_DIR	= include
SRC_DIR		= src
OBJ_DIR		= obj

#--------------- FILES ----------------#

INC			= -I $(INCLUDE_DIR)

SRC		= ft_print_n.c \
			ft_print_ptr.c \
			ft_print_un.c \
			ft_print_x.c \
			ft_print_X2.c \
			ft_printf.c \

OBJ		= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

#--------------- COMPILATION ---------------#

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g $(INC)

#--------------- RULES ---------------#

obj/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^

all: $(NAME)

$(NAME): $(OBJ)
	@ar -cr $(OUTPUT) $(OBJ)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(OUTPUT)

re: fclean all

.PHONY: all re clean fclean
