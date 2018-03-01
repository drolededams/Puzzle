# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/12 15:32:27 by dgameiro          #+#    #+#              #
#    Updated: 2018/03/01 16:37:38 by dgameiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c src/strcomsplit.c src/verif.c src/math.c src/generation.c src/exit.c src/parsing.c src/lib.c src/print.c src/mem.c \
	  src/heap.c src/tree.c src/state.c src/start.c

INC = -I./inc

NAME = N-Puzzle

FLAGS = -Wall -Werror -Wextra


$(NAME):
	@make -C ./libft
	@gcc $(FLAGS) $(SRC) $(INC) -L libft/ -lft -o $(NAME)

all: $(NAME)

clean :
	@make -C libft/ fclean

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all
