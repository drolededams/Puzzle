/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N-Puzzle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:03:58 by dgameiro          #+#    #+#             */
/*   Updated: 2018/02/28 19:06:33 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPuzzle_H
# define NPuzzle_H
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include <time.h>
# define BAD_LINE 1
# define SIZES 2
# define TOO_LOW 3
# define NO_SIZE 4
# define BAD_FILE 5
# define NUMBER_MISSING 1
# define IMPOSSIBLE 2
# define H_SIZE heap->size
# define H_MAX heap->max
# define H_LAST heap->tab[heap->size]
# define H_I heap->tab[i]
# define H_I_F H_I->cost + H_I->heu
# define H_FATH heap->tab[father]
# define H_FATH_F H_FATH->cost + H_FATH->heu
# define H_DOWN heap->tab[i_down]
# define H_DOWN_1 heap->tab[i_down + 1]
# define H_DOWN_F heap->tab[i_down]->cost + heap->tab[i_down]->heu
# define H_DOWN_1_F heap->tab[i_down + 1]->cost + heap->tab[i_down + 1]->heu
# define H_UP heap->tab[i_up]
# define H_UP_F heap->tab[i_up]->cost + heap->tab[i_up]->heu
# define HASH state->hash
# define ID state->id

typedef struct		s_puzzle_data
{
	int		size;
	int		line;
	int*	puzzle;
	int* state_coor;
	int* goal_coor;
	int		(*coor[4])(int d, int v, int im, int size);
}					t_puzzle_data;

typedef struct		s_state
{
	uint64_t id;
	int		cost;
	int		heu;
	int		i_heap;
	int		hash;
	int		closed;
	int		*coor;
	int		*value;
	struct s_state *pre;
	struct s_state *left;
	struct s_state *right;
}					t_state;

typedef struct		s_heap
{
	t_state		**tab;
	int			size;
	int			max;
}					t_heap;

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

t_heap		*mem_heap(void);
void	realloc_heap(t_heap *heap);
void	push_heap(t_heap *heap, t_state *state);
t_state		*pop_heap(t_heap *heap);
void	up_heap(t_heap *heap, int i);
void		down_heap(t_heap *heap);
void		free_heap(t_heap *heap);

void	add_node(t_state **root, t_state *state);
t_state		*search_node(t_state *root, uint64_t id);
#endif
