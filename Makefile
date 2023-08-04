# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 20:05:44 by dde-sott          #+#    #+#              #
#    Updated: 2023/05/24 20:05:44 by dde-sott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Name of the project
NAME = pipex

#Compiler
CC = cc
CC_FLAGS = -Wall -Wextra -Werror -g -I incs -I libft/incs

#.c files
SOURCE = pipex utils
		 
# #transformar os ficheiros em ficheiro .c
C_SOURCE = $(SOURCE:%=%.c)

#Object files para transformar todos os ficheiros .c para .o?
O_FILES = $(C_SOURCE:.c=.o)

LIBFT = libft/libft.a

all: $(LIBFT) $(NAME) 

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(O_FILES)
	$(CC) $(CC_FLAGS) $(O_FILES) -L libft/ -lft -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -f $(O_FILES)
	$(MAKE) -C libft/ clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft/ fclean

re: fclean $(NAME)