/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_n.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:52:04 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/28 14:59:50 by dgameiro         ###   ########.fr       */
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
