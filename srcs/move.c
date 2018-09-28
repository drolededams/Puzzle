/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 14:56:11 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/28 14:57:19 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

uint64_t		down_tile(t_state *state, unsigned int size)
{
	uint64_t id_successor;
	uint64_t blank;
	uint64_t shifted;

	if (state->coor[0] / size == 0)
		return (0);
	else
	{
		id_successor = state->id;
		blank = 15;
		shifted = state->value[state->coor[0] - size];
		id_successor &= ~(blank << (state->coor[0] - size) * 4);
		id_successor |= shifted << (state->coor[0] * 4);
	}
	return (id_successor);
}

uint64_t		up_tile(t_state *state, unsigned int size)
{
	uint64_t id_successor;
	uint64_t blank;
	uint64_t shifted;
	uint64_t test;

	if (state->coor[0] / size == size - 1)
		return (0);
	else
	{
		id_successor = state->id;
		blank = 15;
		shifted = state->value[state->coor[0] + size];
		test = ~(blank << (state->coor[0] + size) * 4);
		id_successor &= ~(blank << (state->coor[0] + size) * 4);
		id_successor |= shifted << (state->coor[0] * 4);
	}
	return (id_successor);
}

uint64_t		right_tile(t_state *state, unsigned int size)
{
	uint64_t id_successor;
	uint64_t blank;
	uint64_t shifted;

	if (state->coor[0] % size == 0)
		return (0);
	else
	{
		id_successor = state->id;
		blank = 15;
		shifted = state->value[state->coor[0] - 1];
		id_successor &= ~(blank << (state->coor[0] - 1) * 4);
		id_successor |= shifted << (state->coor[0] * 4);
	}
	return (id_successor);
}

uint64_t		left_tile(t_state *state, unsigned int size)
{
	uint64_t id_successor;
	uint64_t blank;
	uint64_t shifted;

	if (state->coor[0] % size == size - 1)
		return (0);
	else
	{
		id_successor = state->id;
		blank = 15;
		shifted = state->value[state->coor[0] + 1];
		id_successor &= ~(blank << (state->coor[0] + 1) * 4);
		id_successor |= shifted << (state->coor[0] * 4);
	}
	return (id_successor);
}
