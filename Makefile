# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/12 15:32:27 by dgameiro          #+#    #+#              #
#    Updated: 2018/09/28 14:58:59 by dgameiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

SRC_PATH = srcs

SRC_NAME = main.c strcomsplit.c verif.c math.c generation.c exit.c parsing.c lib.c print.c mem.c heap.c tree.c state.c start.c heuristic.c start_n.c state_n.c tree_n.c file_print.c free.c lib_2.c heap_2.c coor_calc.c heuristic_choice.c heuristic_choice.c heuristic_choice.c heuristic_choice.c start_n_2.c start_2.c move.c move_n.c

OBJ_PATH = objs

CPPFLAGS = -Iinc

LDFLAGS = -Llibft
LDLIBS = -lft

NAME = N-Puzzle

CC = gcc
CFLAGS = -Wall -Wextra -Werror

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean :
	@make clean -C libft
	@rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean : clean
	@make fclean -C libft
	@rm -fv $(NAME)

re : fclean all
