/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:12:45 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/02 22:19:43 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

t_state		*mem_state_4(uint64_t id, t_state *pre, unsigned int size, unsigned int *goal)
{
	t_state *state;

	if (!(state = (t_state*)(malloc(sizeof(t_state)))))
		exit_alloc_failed();
	if (!(state->value = (unsigned int*)malloc(sizeof(unsigned int) * size)))
		exit_alloc_failed();
	if (!(state->coor = (unsigned int*)malloc(sizeof(unsigned int) * size)))
		exit_alloc_failed(); //state_corr sert ptete a rien
	state->id = id;
	state->pre = pre;
	state->left = NULL;
	state->right = NULL;
	puz_state(state, size);
	state->heu = manhattan_dist(state->value, goal, size);
	return (state);
}

void	puz_state(t_state *state, unsigned int size)
{
	unsigned int i; 

	i = 0;
	while(i < size)
	{
		state->coor[i] = (state->id >> 4 * i) & 0xF;
		state->value[state->coor[i]] = i;
		i++;
	}
}

uint64_t	id_state(unsigned int *tab, unsigned int size)
{
	uint64_t i;
	uint64_t id;

	i = 0;
	id = 0;
	while(i < size)
	{
		id |= i << (tab[i] * 4);
		i++;
	}
	return (id);
}

unsigned int hash_table(uint64_t id)
{
	unsigned int x;
	unsigned int i;

	x = 1;
	i = 0;
	while(x != 0)
	{
		x = (id >> 4 * i) & 0xF;
		i++;
	}
	return ((id & 1023));
}

uint64_t	down_tile(t_state *state, unsigned int size)
{
	uint64_t id_successor;
	uint64_t blank;
	uint64_t shifted;

	if (state->value[0] / size == 0)
		return (0);
	else
	{
		id_successor = state->id;
		blank = 15;
		shifted = state->coor[state->value[0] - size];
		id_successor &= ~(blank << (state->value[0] - size) * 4);
		id_successor |= shifted << (state->value[0] * 4);
	}
	return (id_successor);
}

uint64_t	up_tile(t_state *state, unsigned int size)
{
	uint64_t id_successor;
	uint64_t blank;
	uint64_t shifted;
	uint64_t test;

	if (state->value[0] / size == size - 1)
		return (0);
	else
	{
		id_successor = state->id;
		blank = 15;
		shifted = state->coor[state->value[0] + size];
		test = ~(blank << (state->value[0] + size) * 4);
		id_successor &= ~(blank << (state->value[0] + size) * 4);
		id_successor |= shifted << (state->value[0] * 4);
	}
	return (id_successor);
}

uint64_t	right_tile(t_state *state, unsigned int size)
{
	uint64_t id_successor;
	uint64_t blank;
	uint64_t shifted;

	if (state->value[0] % size == 0)
		return (0);
	else
	{
		id_successor = state->id;
		blank = 15;
		shifted = state->coor[state->value[0] - 1];
		id_successor &= ~(blank << (state->value[0] - 1) * 4);
		id_successor |= shifted << (state->value[0] * 4);
	}
	return (id_successor);
}

uint64_t	left_tile(t_state *state, unsigned int size)
{
	uint64_t id_successor;
	uint64_t blank;
	uint64_t shifted;

	if (state->value[0] % size == size - 1)
		return (0);
	else
	{
		id_successor = state->id;
		blank = 15;
		shifted = state->coor[state->value[0] + 1];
		id_successor &= ~(blank << (state->value[0] + 1) * 4);
		id_successor |= shifted << (state->value[0] * 4);
	}
	return (id_successor);
}
