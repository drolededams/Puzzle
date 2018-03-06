/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N-Puzzle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:03:58 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/06 10:59:17 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPuzzle_H
# define NPuzzle_H
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include <inttypes.h>
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
# define H_I_IH heap->tab[i]->i_heap
# define H_I_F H_I->cost + H_I->heu
# define H_FATH heap->tab[father]
# define H_FATH_IH heap->tab[father]->i_heap
# define H_FATH_F H_FATH->cost + H_FATH->heu
# define H_DOWN heap->tab[i_down]
# define H_DOWN_IH heap->tab[i_down]->i_heap
# define H_DOWN_1 heap->tab[i_down + 1]
# define H_DOWN_F heap->tab[i_down]->cost + heap->tab[i_down]->heu
# define H_DOWN_1_F heap->tab[i_down + 1]->cost + heap->tab[i_down + 1]->heu
# define H_UP heap->tab[i_up]
# define H_UP_IH heap->tab[i_up]->i_heap
# define H_UP_F heap->tab[i_up]->cost + heap->tab[i_up]->heu
# define HASH state->hash
# define ID state->id
# define HEU_CHOICE data->heu_choice
# define SIZE data->size
# define AREA data->area

typedef struct		s_state
{
	uint64_t id;
	int		cost;
	int		heu;
	int		i_heap;
	int		hash;
	unsigned int		*value;
	unsigned int		*coor;
	struct s_state *pre;
	struct s_state *left;
	struct s_state *right;
}					t_state;

typedef struct		s_puzzle_data
{
	unsigned int		size;
	unsigned int		area;
	unsigned int		line;
	unsigned int		heu_choice;
	int		search_cost;
	unsigned int*	puzzle;
	unsigned int* state_coor;
	unsigned int* goal_coor;
	unsigned int* goal_value;
	int		(*coor[4])(int d, int v, int im, int size);
	unsigned int		(*heu[3])(unsigned int *state, struct s_puzzle_data *data);
	uint64_t (*move[4])(t_state *state, unsigned int size);
}					t_puzzle_data;


typedef struct		s_heap
{
	t_state		**tab;
	int			size;
	int			max;
}					t_heap;

void	get_file(char *file, t_puzzle_data *data);
int		good_line(char *line);
void	analyse_line(char *line, t_puzzle_data *data);
unsigned int		mat_len_y(char **mat);
void	mem_puzzle(t_puzzle_data *data);
void	exit_bad_file(char **line, char **split, t_puzzle_data *data, int code);
void	exit_bad_file2(t_puzzle_data *data);
void	exit_bad_line(char **line, t_puzzle_data *data, int code);
void	exit_alloc_failed(void);
char	**strcomsplit(const char *s, char c);
void	free_tab(char **tab);
void	verif_puzzle(t_puzzle_data *data);
void	good_numbers(t_puzzle_data *data);
int		is_in_puzzle(t_puzzle_data *data, unsigned int n);
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
void	exit_bad_puzzle(t_puzzle_data *data, int code);
void	is_soluble(t_puzzle_data *data, int random);
int		permutation_calc(t_puzzle_data *data);
void	coor_alloc(t_puzzle_data *data);
unsigned int		*tab_copy(unsigned int *tab, int size);
void generation(t_puzzle_data *data);
int size_verif(char *s);
int		is_num(char *s);
void	make_npuzzle(t_puzzle_data *data);
void print_coor(unsigned int *tab, int n);
void	random_tab(unsigned int *tab, int n);
void swap_tabint(unsigned int *tab, int a, int b);
void	print_puzzle(unsigned int *tab, int n);
void	print_tabint(unsigned int *tab, int n);
void		print_bits(uint64_t n);

t_heap		*mem_heap(void);
void	realloc_heap(t_heap *heap);
void	push_heap(t_heap *heap, t_state *state);
t_state		*pop_heap(t_heap *heap);
void	up_heap(t_heap *heap, int i);
void		down_heap(t_heap *heap);
void		free_heap(t_heap *heap);

void	add_node(t_state **root, t_state *state);
t_state		*search_node(t_state *root, uint64_t id);
t_state		**mem_hash_table(void);

t_state		*mem_state_4(uint64_t id, t_state *pre, t_puzzle_data *data);
void	puz_state(t_state *state, unsigned int area);
uint64_t	id_state(unsigned int *tab, unsigned int area);
unsigned int hash_table(uint64_t id, unsigned int area);
uint64_t	left_tile(t_state *state, unsigned int size);
uint64_t	right_tile(t_state *state, unsigned int size);
uint64_t	up_tile(t_state *state, unsigned int size);
uint64_t	down_tile(t_state *state, unsigned int size);

void	pre_start_a(t_puzzle_data *data);
void	start_a(t_heap *heap, uint64_t id_goal, t_state **hash_tab, t_puzzle_data *data);

unsigned int		manhattan_dist(unsigned int *state, t_puzzle_data *data);
unsigned int	hamming_dist(unsigned int *state, t_puzzle_data *data);
unsigned int	linear_conflict(unsigned int *state, t_puzzle_data *data);
void	search_choice(t_puzzle_data *data);
void	heuristic_choice(t_puzzle_data *data);
int		choice_verif(char *s);
#endif
