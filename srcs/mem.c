/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:57:48 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/27 19:59:06 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

void			mem_puzzle(t_puzzle_data *data)
{
	if (!(data->puzzle = (unsigned int*)malloc(sizeof(unsigned int) *
		data->area)))
		exit_alloc_failed();
}

void			coor_alloc(t_puzzle_data *data)
{
	if (!(data->state_coor = (unsigned int*)malloc(sizeof(unsigned int) *
		data->area)))
		exit_alloc_failed();
	if (!(data->goal_coor = (unsigned int*)malloc(sizeof(unsigned int) *
		data->area)))
		exit_alloc_failed();
	if (!(data->goal_value = (unsigned int*)malloc(sizeof(unsigned int) *
		data->area)))
		exit_alloc_failed();
}

unsigned int	*puz_alloc(unsigned int area)
{
	unsigned int *tab;

	if (!(tab = (unsigned int*)malloc(sizeof(unsigned int) * area)))
		exit_alloc_failed();
	return (tab);
}
