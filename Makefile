# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/28 15:25:20 by achraiti          #+#    #+#              #
#    Updated: 2024/03/21 01:31:14 by achraiti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME2 = pipex_bonus

SRC_D = src

BONUS = bonus

SRC = $(SRC_D)/utils.c $(SRC_D)/utils2.c $(SRC_D)/pipex.c

SRC2 = $(BONUS)/bonus.c $(BONUS)/utils.c \
	$(BONUS)/utils2.c $(BONUS)/bonus2.c \
	$(BONUS)/here_doc.c

OBJ = $(SRC:.c=.o)

OBJ2 = $(SRC2:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

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

push:
	git add .
	git commit -m "update"
	git push

re: fclean all

.PHONY: clean re all fclean

.SECONDARY: $(OBJ) $(OBJ2)
