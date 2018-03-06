/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:43:42 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/06 18:57:56 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	swap_tabint(unsigned int *tab, int a, int b)
{
	unsigned int tmp;

	tmp = tab[a];
	tab[a] = tab[b];
	tab[b] = tmp;
}

void	func_init(t_puzzle_data *data)
{
	data->coor[0] = coor_top;
	data->coor[1] = coor_right;
	data->coor[2] = coor_bottom;
	data->coor[3] = coor_left;
	data->heu[0] = linear_conflict;
	data->heu[1] = manhattan_dist;
	data->heu[2] = hamming_dist;
	data->move[0] = up_tile;
	data->move[1] = down_tile;
	data->move[2] = left_tile;
	data->move[3] = right_tile;
	data->move_n[0] = up_tile_n;
	data->move_n[1] = down_tile_n;
	data->move_n[2] = left_tile_n;
	data->move_n[3] = right_tile_n;
}

int		is_num(char *s)
{
	int i;

	i = 0;
	while (s[i])
		if (!ft_isdigit(s[i++]))
			return (0);
	return (i);
}

unsigned int		mat_len_y(char **mat)
{
	unsigned  i;

	i = 0;
	while (mat[i] != NULL)
		i++;
	return (i);
}

unsigned int		*tab_copy(unsigned int *tab, int size)
{
	unsigned int *copy;
	int i;

	if (!(copy = (unsigned int*)malloc(sizeof(unsigned int) * size)))
		exit_alloc_failed();//mem a lib
	i = -1;
	while (++i < size)
		copy[i] = tab[i];
	return (copy);
}

void		state_tab_copy(t_state *state, unsigned int *coor, unsigned int *val, unsigned int area)
{
	unsigned int i;

	i = 0;
	while (i < area)
	{
		coor[i] = state->coor[i];
		val[i] = state->value[i];
		i++;
	}
}
