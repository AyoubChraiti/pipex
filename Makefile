# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/28 15:25:20 by achraiti          #+#    #+#              #
#    Updated: 2024/02/28 18:40:19 by achraiti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME2 = pipex_bonus

SRC =  pipex_utils.c pipex_utils2.c pipex.c

# SRC2 = here_doc.c pipex_bonus_utils.c pipex_utils2.c

SRC2 = pipex_bonus.c pipex_bonus_utils.c pipex_utils2.c

OBJ = $(SRC:.c=.o)

OBJ2 = $(SRC2:.c=.o)

CC = cc

CFLAGS = #-Wall -Wextra -Werror

INCLUDES = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	cd libft && $(MAKE)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) -o $(NAME)
	

bonus: $(NAME2)

$(NAME2): $(OBJ2)
	cd libft && $(MAKE)
	$(CC) $(CFLAGS) $(OBJ2) $(INCLUDES) -o $(NAME2)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf libft/*.o
	rm -rf $(OBJ)
	rm -rf $(OBJ2)

fclean: clean
	rm -rf libft/libft.a
	rm -rf $(NAME)
	rm -rf $(NAME2)

re: fclean all

.PHONY: clean re all fclean
