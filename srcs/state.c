/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:12:45 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/28 14:57:27 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

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
		exit_alloc_failed();
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
