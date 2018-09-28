/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:06:10 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/28 14:46:09 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

unsigned int		hamming_dist(unsigned int *state, t_puzzle_data *data)
{
	unsigned int i;
	unsigned int heu;

	i = 1;
	heu = 0;
	while (i < data->area)
	{
		if (data->goal_coor[i] != state[i])
			heu++;
		i++;
	}
	return (heu);
}

unsigned int		manhattan_dist(unsigned int *state, t_puzzle_data *data)
{
	unsigned int i;
	unsigned int heu;

	i = 1;
	heu = 0;
	while (i < data->area)
	{
		heu += distance(state[i], data->goal_coor[i], data->size);
		i++;
	}
	return (heu);
}

static unsigned int	calc_linear(unsigned int *state, t_puzzle_data *data,
		unsigned int i, unsigned int j)
{
	unsigned int line;
	unsigned int col;

	line = state[i] / data->size;
	col = state[i] % data->size;
	if (line == (state[j] / data->size) && line ==
			(data->goal_coor[i] / data->size) && line ==
			(data->goal_coor[j] / data->size) && state[i] >
			state[j] && data->goal_coor[i] < data->goal_coor[j])
		return (2);
	else if (col == (state[j] % data->size) && col ==
			(data->goal_coor[i] % data->size) && col ==
			(data->goal_coor[j] % data->size) &&
			state[i] > state[j] && data->goal_coor[i] <
			data->goal_coor[j])
		return (2);
	else
		return (0);
}

unsigned int		linear_conflict(unsigned int *state, t_puzzle_data *data)
{
	unsigned int i;
	unsigned int j;
	unsigned int heu;

	heu = data->heu[1](state, data);
	i = 1;
	while (i < data->area)
	{
		j = 1;
		while (j < data->area)
		{
			if (i != j)
				heu += calc_linear(state, data, i, j);
			j++;
		}
		i++;
	}
	return (heu);
}
