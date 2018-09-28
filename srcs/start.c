/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:30:22 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/28 14:53:10 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

static void	new_state(t_puzzle_data *data, t_heap *heap,
		uint64_t id_successor, t_state **hash_tab)
{
	t_state		*successor;

	data->com_size++;
	successor = mem_state(id_successor, data->cur, data);
	successor->cost = data->cur->cost + data->search_cost;
	push_heap(heap, successor);
	add_node(&hash_tab[hash_table(successor->id, data->area)], successor);
}

static void	update_state(t_puzzle_data *data, t_heap *heap, t_state *successor)
{
	successor->pre = data->cur;
	successor->cost = data->cur->cost + data->search_cost;
	if (!successor->i_heap)
		push_heap(heap, successor);
	else
		up_heap(heap, successor->i_heap);
}

static void	display_result(t_puzzle_data *data, t_heap *heap,
		t_state **hash_tab)
{
	printf("Complexity in Time (States selected) = %u \n", data->com_time);
	printf("Complexity in Size  (States in memory) = %u \n", data->com_size);
	file_print(data->cur, data);
	free_all(data, hash_tab, heap);
}

static void	move_tile(t_puzzle_data *data, t_heap *heap, t_state **hash_tab)
{
	uint64_t	id_successor;
	int			i;
	t_state		*successor;

	i = -1;
	while (++i < 4)
	{
		if ((id_successor = data->move[i](data->cur, data->size)))
		{
			if (!(successor = search_node(hash_tab[
				hash_table(id_successor, data->area)], id_successor)))
				new_state(data, heap, id_successor, hash_tab);
			else if (successor->cost > data->cur->cost +
					data->search_cost)
				update_state(data, heap, successor);
		}
	}
}

void		start_a(t_heap *heap, uint64_t id_goal, t_state **hash_tab,
		t_puzzle_data *data)
{
	int			success;

	success = 0;
	while (heap->size > 0 && !success)
	{
		data->cur = pop_heap(heap);
		data->com_time++;
		if (data->cur->id == id_goal)
			success = 1;
		else
			move_tile(data, heap, hash_tab);
	}
	display_result(data, heap, hash_tab);
}
