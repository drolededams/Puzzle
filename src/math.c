/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:40:13 by dgameiro          #+#    #+#             */
/*   Updated: 2018/02/22 17:36:00 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

/*int		manhattan_dist()
{

}
*/

int		distance(t_coor a, t_coor b)
{
	return (ft_sqrt(ft_power(a.x - b.x, 2)) + ft_sqrt(ft_power(a.y - b.y, 2)));
}

void	func_init(t_puzzle_data *data)
{
	data->coor[0] = coor_top;
	data->coor[1] = coor_right;
	data->coor[2] = coor_bottom;
	data->coor[3] = coor_left;
}

t_coor	coor_top(int d, int v, int im)
{
	t_coor c;

	im = 0;
	c.x = d + v - 1;
	c.y = d;
	return (c);
}

t_coor	coor_right(int d, int v, int im)
{
	t_coor c;

	c.x = im;
	c.y = d + v;
	return (c);
}

t_coor	coor_bottom(int d, int v, int im)
{
	t_coor c;
	
	d = 0;
	c.x = im - v;
	c.y = im;
	return (c);
}

t_coor	coor_left(int d, int v, int im)
{
	t_coor c;

	c.x = d;
	c.y = im - v;
	return (c);
}

t_coor find_final_coor(t_puzzle_data *data, int value)
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
	while(value > seg_size)
	{
		value -= seg_size;
		corner += 1;
		seg_size -= corner % 2;
	}
	border_d = corner / 4;
	side = corner % 4;
	indice_max = data->size - 1 - border_d;
	return (data->coor[side](border_d, value, indice_max));
}
