/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_n.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:54:20 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/08 11:17:41 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "N-Puzzle.h"

void	pre_start_a_n(t_puzzle_data *data)
{
	t_state		*start;
	t_heap		*heap;
	t_state		**hash_tab;
	uint64_t	id_goal;

	hash_tab = mem_hash_table_n();
	start = mem_state_n(id_state_n(data->state_coor, data->area), data->state_coor, NULL, data);
	start->cost = 0;
	id_goal = id_state_n(data->goal_coor, data->area);
	heap = mem_heap();
	push_heap(heap, start);
	add_node(&hash_tab[hash_table_n(start->coor, start->value, data->area)], start);
	start_a_n(heap, id_goal, hash_tab, data);
	//lib mem data
}

void	start_a_n(t_heap *heap, uint64_t id_goal, t_state **hash_tab, t_puzzle_data *data)
{
	int				success;
	int				i;
	int				count;
	int				count_2;
	uint64_t		id_successor;
	unsigned int	*su_coor;
	unsigned int	*su_val;
	t_state			*state;
	t_state			*successor;

	su_coor = puz_alloc(data->area);
	su_val = puz_alloc(data->area);
	success = 0;
	count = 0;
	count_2 = 1;
	while (H_SIZE > 0 && !success)
	{
		count++;
		state = pop_heap(heap);
		if (state->id == id_goal && same_state(state->coor, data->goal_coor, data->area))
			success = 1;
		else
		{
			i = -1;
			while (++i < 4)
			{
				if ((id_successor = data->move_n[i](state, su_coor, su_val, data->size)))
				{
					if (!(successor = search_node_n(hash_tab[hash_table_n(su_coor, su_val, data->area)], id_successor, su_coor, data->area)))
					{
						count_2++;
						successor = mem_state_n(id_successor, su_coor, state, data);
						successor->cost = state->cost + data->search_cost;
						push_heap(heap, successor);
						add_node(&hash_tab[hash_table_n(successor->coor, successor->value, data->area)], successor);
					}
					else if (successor->cost > state->cost + data->search_cost)
					{
						successor->pre = state;
						successor->cost = state->cost + data->search_cost;
						if (!successor->i_heap)
							push_heap(heap, successor);
						else
							up_heap(heap, successor->i_heap);
					}
				}
			}
		}
	}
	ft_memdel((void**)&su_coor);
	ft_memdel((void**)&su_val);
	printf("Complexity in Time (states selected) = %d \n", count);
	printf("Complexity in Size  (States in memory) = %d \n", count_2);
	file_print(state, data);
}
