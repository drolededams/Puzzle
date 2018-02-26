/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:57:48 by dgameiro          #+#    #+#             */
/*   Updated: 2018/02/26 18:07:59 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	mem_puzzle(t_puzzle_data *data)
{
	if (!(data->puzzle = (int*)malloc(sizeof(int) * data->size * data->size)))
		exit_alloc_failed();
}

void	coor_alloc(t_puzzle_data *data)
{
	if (!(data->state_coor = (int*)malloc(sizeof(int) * ft_power(data->size, 2))))
		exit_alloc_failed();
	if (!(data->goal_coor = (int*)malloc(sizeof(int) * ft_power(data->size, 2))))
		exit_alloc_failed();
}
