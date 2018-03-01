/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:12:45 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/01 20:37:07 by dgameiro         ###   ########.fr       */
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
	return (id & 1023);
}
