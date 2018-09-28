/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coor_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 14:40:12 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/28 14:40:26 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

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
