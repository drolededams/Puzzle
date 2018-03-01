/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:30:22 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/01 20:37:08 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	pre_start_a(t_puzzle_data *data)
{
	t_state	*start;
	t_heap	*heap;
	t_state **hash_tab;
	unsigned int size;
	uint64_t id_goal;

	hash_tab = mem_hash_table();
	size = data->size * data->size;
	start = mem_state_4(id_state(data->state_coor, size), NULL, size, data->goal_coor);
	id_goal = id_state(data->goal_coor, size);
	heap = mem_heap();
	push_heap(heap, start);
	add_node(&hash_tab[hash_table(start->id)], start);
	start_a(heap, id_goal, hash_tab, size);
	//lib mem data
}

void	start_a(t_heap *heap, unsigned int id_goal, t_state **hash_tab, unsigned int size)
{
	int success;
	t_state *state;
	t_state *successor;

	success = 0;
	while (H_SIZE > 0 && !success)
	{
		state = pop_heap(heap); 
		if (state->id == id_goal)
			success = 1;
		else
		{
			while(succssor)
			{
				if (successor != hash_tab)
				{
					successor = mem_state_4(id_successor, state, size, id_goal);
					push_heap(heap, successor);
					add_node(&hash_tab[hash_table(successor->id)], successor);
					successor->cost = state->cost + 1;
				}
				else if (successor->cost > state->cost + 1)
				{
					successor->pre = state;
					successor->cost = state->cost + 1;
					if(!successor->i_heap)
						push_heap(heap, successor);
					else
						up_heap(heap, successor->i_heap);
				}
			}
		}
	}
}
