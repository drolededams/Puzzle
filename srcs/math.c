/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:40:13 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/28 14:40:19 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

int		distance(int a, int b, int size)
{
	return (ft_sqrt(ft_power((a / size) - (b / size), 2)) +
		ft_sqrt(ft_power((a % size) - (b % size), 2)));
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
