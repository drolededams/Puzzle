/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:12:45 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/19 19:00:32 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

t_state			*mem_state(uint64_t id, t_state *pre, t_puzzle_data *data)
{
	t_state *state;

	if (!(state = (t_state*)(malloc(sizeof(t_state)))))
		exit_alloc_failed();
	if (!(state->value = (unsigned int*)malloc(sizeof(unsigned int) *
		data->area)))
		exit_alloc_failed();
	if (!(state->coor = (unsigned int*)malloc(sizeof(unsigned int) *
		data->area)))
		exit_alloc_failed(); //state_corr sert ptete a rien
	state->id = id;
	state->pre = pre;
	state->left = NULL;
	state->right = NULL;
	puz_state(state, data->area);
	if (data->heu_choice)
		state->heu = data->heu[data->heu_choice - 1](state->coor, data);
	else
		state->heu = 0;
	return (state);
}

void			puz_state(t_state *state, unsigned int area)
{
	unsigned int i;

	i = 0;
	while (i < area)
	{
		state->value[i] = (state->id >> 4 * i) & 0xF;
		state->coor[state->value[i]] = i;
		i++;
	}
}

uint64_t		id_state(unsigned int *tab, unsigned int area)
{
	uint64_t i;
	uint64_t id;

	i = 0;
	id = 0;
	while (i < area)
	{
		id |= i << (tab[i] * 4);
		i++;
	}
	if (id == 0)
		ft_putendl("pb id");
	return (id);
}

unsigned int	hash_table(uint64_t id, unsigned int area)
{
	unsigned int x;
	unsigned int i;
	unsigned int hash;

	x = 1;
	i = 0;
	hash = 0;
	while (x != 0)
	{
		x = (id >> 4 * i) & 0xF;
		i++;
	}
	if (i == 1)
	{
		hash = (id >> 4) & 0xF;
		hash = hash << 8;
	}
	else if (i == area)
	{
		hash = i - 1;
		hash = (hash << 4) | ((id >> 4 * (i - 2)) & 0xF);
	}
	else
	{
		hash = (id >> (4 * i)) & 0xF;
		hash = (hash << 4) | i;
		hash = (hash << 4) | (id >> 4 * (i - 2) & 0xF);
	}
	return (hash & 1023);
}

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
