/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 14:58:11 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/28 14:58:39 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

uint64_t		down_tile_n(t_state *state, unsigned int *coor,
	unsigned int *val, unsigned int size)
{
	unsigned int shifted;

	if (state->coor[0] / size == 0)
		return (0);
	else
	{
		state_tab_copy(state, coor, val, size * size);
		shifted = state->value[state->coor[0] - size];
		coor[shifted] = state->coor[0];
		coor[0] = state->coor[shifted];
		val[coor[shifted]] = shifted;
		val[coor[0]] = 0;
	}
	return (id_state_n(coor, size * size));
}

uint64_t		up_tile_n(t_state *state, unsigned int *coor,
	unsigned int *val, unsigned int size)
{
	unsigned int shifted;

	if (state->coor[0] / size == size - 1)
		return (0);
	else
	{
		state_tab_copy(state, coor, val, size * size);
		shifted = state->value[state->coor[0] + size];
		coor[shifted] = state->coor[0];
		coor[0] = state->coor[shifted];
		val[coor[shifted]] = shifted;
		val[coor[0]] = 0;
	}
	return (id_state_n(coor, size * size));
}

uint64_t		right_tile_n(t_state *state, unsigned int *coor,
	unsigned int *val, unsigned int size)
{
	unsigned int shifted;

	if (state->coor[0] % size == 0)
		return (0);
	else
	{
		state_tab_copy(state, coor, val, size * size);
		shifted = state->value[state->coor[0] - 1];
		coor[shifted] = state->coor[0];
		coor[0] = state->coor[shifted];
		val[coor[shifted]] = shifted;
		val[coor[0]] = 0;
	}
	return (id_state_n(coor, size * size));
}

uint64_t		left_tile_n(t_state *state, unsigned int *coor,
	unsigned int *val, unsigned int size)
{
	unsigned int shifted;

	if (state->coor[0] % size == size - 1)
		return (0);
	else
	{
		state_tab_copy(state, coor, val, size * size);
		shifted = state->value[state->coor[0] + 1];
		coor[shifted] = state->coor[0];
		coor[0] = state->coor[shifted];
		val[coor[shifted]] = shifted;
		val[coor[0]] = 0;
	}
	return (id_state_n(coor, size * size));
}
