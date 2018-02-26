/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:29:23 by dgameiro          #+#    #+#             */
/*   Updated: 2018/02/26 17:59:48 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	verif_puzzle(t_puzzle_data *data)
{
	ft_putendl("Good numbers");
	good_numbers(data);
	ft_putendl("Is Soluble");
	is_soluble(data, 0);
	ft_putendl("fin");
}

void	good_numbers(t_puzzle_data *data)
{
	int i;

	i = -1;
	while (++i < data->size * data->size)
		if (!(is_in_puzzle(data, i)))
			exit_bad_puzzle(data, NUMBER_MISSING);
}

int		is_in_puzzle(t_puzzle_data *data, int n)
{
	int i;
	int j;

	i = -1;
	j = data->size * data->size;
	while (++i < j)
		if (data->puzzle[i] == n)
			return (1);
	return (0);
}

void	is_soluble(t_puzzle_data *data, int random)
{
	int i;
	int blank_dis;
	int permutation;
	int n;

	i = -1;
	coor_alloc(data);
	func_init(data);
	n = data->size * data->size;
	while (++i < n)
	{
		data->state_coor[data->puzzle[i]] = i;
		data->goal_coor[data->puzzle[i]] = find_final_coor(data, data->puzzle[i]);
	}
	blank_dis = distance(data->state_coor[0], data->goal_coor[0], data->size) % 2;
	permutation = permutation_calc(data) % 2;
	ft_putendl("gen");
	print_coor(data->state_coor, n);
	ft_putendl("sol");
	print_coor(data->goal_coor, n);
	if (blank_dis == permutation)
		ft_putendl("Puzzle Soluble");
	else if (random)
	{
		ft_putendl("Puzzle Non Soluble. Generation d'un nouveau");
		make_npuzzle(data, n);
	}
	else
		exit_bad_puzzle(data, IMPOSSIBLE);
}
