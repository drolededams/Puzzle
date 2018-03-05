/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:30:22 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/05 19:38:55 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	pre_start_a(t_puzzle_data *data)
{
	t_state	*start;
	t_heap	*heap;
	t_state **hash_tab;
	uint64_t id_goal;

	hash_tab = mem_hash_table();
	start = mem_state_4(id_state(data->state_coor, data->area), NULL, data);
	start->cost = 0;
	printf("%" PRIu64 "\n", start->id);
	id_goal = id_state(data->goal_coor, data->area);
	printf("%" PRIu64 "\n", id_goal);
	heap = mem_heap();
	push_heap(heap, start);
	add_node(&hash_tab[hash_table(start->id)], start);
	start_a(heap, id_goal, hash_tab, data);
	//lib mem data
}

void	start_a(t_heap *heap, uint64_t id_goal, t_state **hash_tab, t_puzzle_data *data)
{
	int success;
	int i;
	int count;
	int count_2;
	uint64_t id_successor;
	int max_hsize;
	t_state *state;
	t_state *successor;
	success = 0;
	count = 0;
	count_2 = 1;
	max_hsize = H_SIZE;
	while (H_SIZE > 0 && !success)
	{
		count++;
		if(H_SIZE > max_hsize)
			max_hsize = H_SIZE;
		state = pop_heap(heap); 
		if (state->id == id_goal)
			success = 1;
		else
		{
			i = -1;
			while(++i < 4)
			{
				if ((id_successor = data->move[i](state, data->size)))
				{
					if (!(successor = search_node(hash_tab[hash_table(id_successor)], id_successor)))
					{
						count_2++;
						successor = mem_state_4(id_successor, state, data);
						successor->cost = state->cost + data->search_cost;
						push_heap(heap, successor);
						add_node(&hash_tab[hash_table(successor->id)], successor);
					}
					else if (successor->cost > state->cost + data->search_cost)
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
	int tour;
	tour = 0;
	ft_putendl("Display result");
	while(state != NULL)
	{
		tour++;
		print_coor(state->value, data->area);
		printf("%" PRIu64 "\n", state->id);
		printf("heuristique = %u \n", state->heu);
		printf("cout = %u \n", state->cost);
		printf("hash = %u \n", hash_table(state->id));
		ft_putendl("pre");
		state = state->pre;
	}
	printf("etape = %d \n", tour);
	printf("state visited = %d \n", count);
	printf("cout memoire = %d \n", count_2);
	printf("Max HSIZE = %d \n", max_hsize);
	printf("final HSIZE = %d \n", H_SIZE);
}
