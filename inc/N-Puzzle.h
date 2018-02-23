/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N-Puzzle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:03:58 by dgameiro          #+#    #+#             */
/*   Updated: 2018/02/23 17:56:43 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPuzzle_H
# define NPuzzle_H
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <time.h>
# define BAD_LINE 1
# define SIZES 2
# define TOO_LOW 3
# define NO_SIZE 4
# define NUMBER_MISSING 1
# define IMPOSSIBLE 2

typedef struct		s_coor
{
	int x;
	int y;
}					t_coor;

typedef struct		s_puzzle_data
{
	int		size;
	int		line;
	int**	puzzle;
	t_coor* state_coor;
	t_coor* goal_coor;
	t_coor	(*coor[4])(int d, int v, int im);
}					t_puzzle_data;

void	get_file(char *file, t_puzzle_data *data);
int		good_line(char *line);
void	analyse_line(char *line, t_puzzle_data *data);
int		tablen(char **tab);
void	mem_puzzle(t_puzzle_data *data);
void	exit_bad_file(char **line, t_puzzle_data *data, int code);
void	exit_alloc_failed(void);
char	**strcomsplit(const char *s, char c);
void	free_tab(char **tab);
void	verif_puzzle(t_puzzle_data *data);
void	good_numbers(t_puzzle_data *data);
int		is_in_puzzle(t_puzzle_data *data, int n);
void	exit_bad_puzzle(t_puzzle_data *data, int code);
int		distance(t_coor a, t_coor b);
void	func_init(t_puzzle_data *data);
t_coor	coor_top(int d, int v, int im);
t_coor	coor_right(int d, int v, int im);
t_coor	coor_bottom(int d, int v, int im);
t_coor	coor_left(int d, int v, int im);
t_coor find_final_coor(t_puzzle_data *data, int value);
void	verif_puzzle(t_puzzle_data *data);
void	good_numbers(t_puzzle_data *data);
int		is_in_puzzle(t_puzzle_data *data, int n);
void	exit_bad_puzzle(t_puzzle_data *data, int code);
t_coor	where_is(t_puzzle_data *data, int value);
void	is_soluble(t_puzzle_data *data);
int		permutation_calc(t_puzzle_data *data);
void	swap_coor(t_coor	*copy, int i, int j);
void	coor_alloc(t_puzzle_data *data);
void	print_coor(t_coor *coor, t_puzzle_data *data);
t_coor	*coor_copy(t_coor *coor, int size);
void generation(t_puzzle_data *data);
int size_verif(char *s);
int		is_num(char *s);
void	make_npuzzle(t_puzzle_data *data);
void print_tabint(int *tab, int n);
void	random_tab(int *rand, int n);
void swap_tabint(int *tab, int a, int b);
t_coor	coor_modulo(int i, int n);
void	random_is_soluble(t_puzzle_data *data, int *tab);
#endif
