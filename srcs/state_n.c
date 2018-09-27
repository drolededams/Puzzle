/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_n.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:52:04 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/27 19:59:06 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

t_state			*mem_state_n(uint64_t id, unsigned int *coor, t_state *pre,
		t_puzzle_data *data)
{
	t_state *state;

	if (!(state = (t_state*)(malloc(sizeof(t_state)))))
		exit_alloc_failed();
	if (!(state->value = (unsigned int*)malloc(sizeof(unsigned int) *
		data->area)))
		exit_alloc_failed();
	if (!(state->coor = (unsigned int*)malloc(sizeof(unsigned int) *
		data->area)))
		exit_alloc_failed();
	state->id = id;
	state->pre = pre;
	state->left = NULL;
	state->right = NULL;
	puz_state_n(state, coor, data->area);
	if (data->heu_choice)
		state->heu = data->heu[data->heu_choice - 1](state->coor, data);
	else
		state->heu = 0;
	return (state);
}

void			puz_state_n(t_state *state, unsigned int *coor,
	unsigned int area)
{
	unsigned int i;

	i = 0;
	while (i < area)
	{
		state->coor[i] = coor[i];
		state->value[state->coor[i]] = i;
		i++;
	}
}

uint64_t		id_state_n(unsigned int *tab, unsigned int area)
{
	uint64_t id;

	id = 941 * (tab[0] + 1) + 919 * tab[14] * (tab[0] + 1) + 863 *
		(tab[0] + 1) * tab[area - 1];
	return (id);
}

unsigned int	hash_table_n(unsigned int *coor, unsigned int *val,
	unsigned int area)
{
	unsigned int hash;
	unsigned int ze;

	ze = coor[0];
	if (ze == 0)
		hash = val[ze + 1];
	else if (ze == (area - 1))
	{
		hash = val[ze - 1];
		hash = (hash << 8) | ze;
	}
	else
	{
		hash = val[ze - 1];
		hash = (hash << 8) | ze;
		hash = (hash << 8) | val[ze + 1];
	}
	return ((97 * hash) & 16777215);
}

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
