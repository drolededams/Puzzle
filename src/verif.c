/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:29:23 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/08 16:34:47 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	verif_puzzle(t_puzzle_data *data)
{
	good_numbers(data);
	coor_alloc(data);
	func_init(data);
	is_soluble(data, 0);
}

void	good_numbers(t_puzzle_data *data)
{
	unsigned int i;

	i = 0;
	while (i < data->area)
	{
		if (!(is_in_puzzle(data, i)))
			exit_bad_puzzle(data, NUMBER_MISSING);
		i++;
	}
}

int		is_in_puzzle(t_puzzle_data *data, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (i < data->area)
	{
		if (data->puzzle[i] == n)
			return (1);
		i++;
	}
	return (0);
}

void	is_soluble(t_puzzle_data *data, int random)
{
	unsigned int	i;
	int				blank_dis;
	int				permutation;
	int				final_coor;

	i = 0;
	while (i < data->area)
	{
		data->state_coor[data->puzzle[i]] = i;
		final_coor = find_final_coor(data, data->puzzle[i]);
		data->goal_coor[data->puzzle[i]] = final_coor;
		data->goal_value[final_coor] = data->puzzle[i];
		i++;
	}
	blank_dis = distance(data->state_coor[0], data->goal_coor[0], data->size) % 2;
	permutation = permutation_calc(data) % 2;
	if (blank_dis == permutation)
	{
		ft_putendl("Start:");
		print_coor(data->state_coor, data->area);
		ft_putendl("Goal:");
		print_coor(data->goal_coor, data->area);
		search_choice(data);
		if (data->size < 5)
			pre_start_a(data);
		else
			pre_start_a_n(data);
	}
	else if (random)
		make_npuzzle(data);
	else
		exit_bad_puzzle(data, IMPOSSIBLE);
}
