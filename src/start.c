/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:30:22 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/26 17:10:03 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	free_tree(t_state *node)
{
	if (node == NULL)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	if (node->value)
		free(node->value);
	if (node->coor)
		free(node->coor);
	free(node);
}

void	pre_start_a(t_puzzle_data *data)
{
	t_state		*start;
	t_heap		*heap;
	t_state		**hash_tab;
	uint64_t	id_goal;

	hash_tab = mem_hash_table();
	start = mem_state(id_state(data->state_coor, data->area), NULL, data);
	start->cost = 0;
	id_goal = id_state(data->goal_coor, data->area);
	heap = mem_heap();
	push_heap(heap, start);
	add_node(&hash_tab[hash_table(start->id, data->area)], start);
	start_a(heap, id_goal, hash_tab, data);
}

void	start_a(t_heap *heap, uint64_t id_goal, t_state **hash_tab,
		t_puzzle_data *data)
{
	int			success;
	int			i;
	int			count;
	int			count_2;
	uint64_t	id_successor;
	t_state		*state;
	t_state		*successor;

	success = 0;
	count = 0;
	count_2 = 1;
	while (H_SIZE > 0 && !success)
	{
		count++;
		state = pop_heap(heap);
		if (state->id == id_goal)
			success = 1;
		else
		{
			i = -1;
			while (++i < 4)
			{
				if ((id_successor = data->move[i](state, data->size)))
				{
					if (!(successor = search_node(hash_tab[
						hash_table(id_successor, data->area)], id_successor)))
					{
						count_2++;
						successor = mem_state(id_successor, state, data);
						successor->cost = state->cost + data->search_cost;
						push_heap(heap, successor);
						add_node(&hash_tab[hash_table(successor->id,
									data->area)], successor);
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
	printf("Complexity in Time (states selected) = %d \n", count);
	printf("Complexity in Size  (States in memory) = %d \n", count_2);
	printf("h size = %d\n", H_SIZE);
	file_print(state, data);
	ft_memdel((void**)&data->state_coor);
	ft_memdel((void**)&data->goal_coor);
	ft_memdel((void**)&data->goal_value);
	ft_memdel((void**)&data->puzzle);
	ft_memdel((void**)&data);
	free_heap(heap);
	int ri;

	ri = 0;
	while (ri < 1024)
	{
		free_tree(hash_tab[ri]);
		ri++;
	}
	ft_memdel((void**)&hash_tab);
}
