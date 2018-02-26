/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N-Puzzle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:03:58 by dgameiro          #+#    #+#             */
/*   Updated: 2018/02/26 17:36:54 by dgameiro         ###   ########.fr       */
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
# define BAD_FILE 5
# define NUMBER_MISSING 1
# define IMPOSSIBLE 2

typedef struct		s_puzzle_data
{
	int		size;
	int		line;
	int*	puzzle;
	int* state_coor;
	int* goal_coor;
	int		(*coor[4])(int d, int v, int im, int size);
}					t_puzzle_data;

void	get_file(char *file, t_puzzle_data *data);
int		good_line(char *line);
void	analyse_line(char *line, t_puzzle_data *data);
int		mat_len_y(char **mat);
void	mem_puzzle(t_puzzle_data *data);
void	exit_bad_file(char **line, char **split, t_puzzle_data *data, int code);
void	exit_bad_file2(t_puzzle_data *data);
void	exit_bad_line(char **line, t_puzzle_data *data, int code);
void	exit_alloc_failed(void);
char	**strcomsplit(const char *s, char c);
void	free_tab(char **tab);
void	verif_puzzle(t_puzzle_data *data);
void	good_numbers(t_puzzle_data *data);
int		is_in_puzzle(t_puzzle_data *data, int n);
void	exit_bad_puzzle(t_puzzle_data *data, int code);
int		distance(int a, int b, int size);
void	func_init(t_puzzle_data *data);
int	coor_top(int d, int v, int im, int size);
int	coor_right(int d, int v, int im, int size);
int	coor_bottom(int d, int v, int im, int size);
int	coor_left(int d, int v, int im, int size);
int find_final_coor(t_puzzle_data *data, int value);
void	verif_puzzle(t_puzzle_data *data);
void	good_numbers(t_puzzle_data *data);
int		is_in_puzzle(t_puzzle_data *data, int n);
void	exit_bad_puzzle(t_puzzle_data *data, int code);
void	is_soluble(t_puzzle_data *data, int random);
int		permutation_calc(t_puzzle_data *data);
void	coor_alloc(t_puzzle_data *data);
int		*tab_copy(int *tab, int size);
void generation(t_puzzle_data *data);
int size_verif(char *s);
int		is_num(char *s);
void	make_npuzzle(t_puzzle_data *data, int n);
void print_coor(int *tab, int n);
void	random_tab(int *tab, int n);
void swap_tabint(int *tab, int a, int b);
void	print_puzzle(int *tab, int n);
#endif
