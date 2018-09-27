/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:40:13 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/27 13:41:48 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

int		distance(int a, int b, int size)
{
	return (ft_sqrt(ft_power((a / size) - (b / size), 2)) +
		ft_sqrt(ft_power((a % size) - (b % size), 2)));
}

int		coor_top(int d, int v, int im, int size)
{
	int x;
	int y;

	im = 0;
	x = d + v - 1;
	y = d;
	return (y * (size) + x);
}

int		coor_right(int d, int v, int im, int size)
{
	int x;
	int y;

	x = im;
	y = d + v;
	return (y * (size) + x);
}

int		coor_bottom(int d, int v, int im, int size)
{
	int x;
	int y;

	d = 0;
	x = im - v;
	y = im;
	return (y * (size) + x);
}

int		coor_left(int d, int v, int im, int size)
{
	int x;
	int y;

	x = d;
	y = im - v;
	return (y * (size) + x);
}

int		find_final_coor(t_puzzle_data *data, int value)
{
	int corner;
	int border_d;
	int seg_size;
	int side;
	int indice_max;

	if (value == 0)
		value = data->size * data->size;
	corner = 0;
	seg_size = data->size;
	while (value > seg_size)
	{
		value -= seg_size;
		corner += 1;
		seg_size -= corner % 2;
	}
	border_d = corner / 4;
	side = corner % 4;
	indice_max = data->size - 1 - border_d;
	return (data->coor[side](border_d, value, indice_max, data->size));
}

int		permutation_calc(t_puzzle_data *data)
{
	unsigned int	i;
	unsigned int	j;
	int				perm;
	unsigned int	*copy;

	i = 0;
	j = 1;
	perm = 0;
	copy = tab_copy(data->state_coor, data->size * data->size);
	while (i < data->area - 1)
	{
		if (copy[i] != data->goal_coor[i] && j < data->area)
		{
			swap_tabint(copy, i, j);
			j++;
			perm++;
		}
		else
		{
			i++;
			j = i + 1;
		}
	}
	ft_memdel((void**)&copy);
	return (perm);
}