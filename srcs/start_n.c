/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_n.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:54:20 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/27 19:27:17 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void		pre_start_a_n(t_puzzle_data *data)
{
	t_state		*start;
	t_heap		*heap;
	t_state		**hash_tab;
	uint64_t	id_goal;

	hash_tab = mem_hash_table_n();
	start = mem_state_n(id_state_n(data->state_coor, data->area),
			data->state_coor, NULL, data);
	start->cost = 0;
	id_goal = id_state_n(data->goal_coor, data->area);
	heap = mem_heap();
	push_heap(heap, start);
	add_node(&hash_tab[hash_table_n(start->coor, start->value, data->area)],
			start);
	data->com_size = 1;
	data->com_time = 0;
	start_a_n(heap, id_goal, hash_tab, data);
}

static void	free_n_all(t_puzzle_data *data, t_state **hash_tab, t_heap *heap)
{
	int i;

	i = 0;
	ft_memdel((void**)&data->state_coor);
	ft_memdel((void**)&data->goal_coor);
	ft_memdel((void**)&data->goal_value);
	ft_memdel((void**)&data->puzzle);
	free_heap(heap);
	while (i < 16777216)
	{
		free_tree(hash_tab[i]);
		i++;
	}
	ft_memdel((void**)&hash_tab);
	ft_memdel((void**)&data);
}

static void	display_n_result(t_puzzle_data *data, t_heap *heap,
		t_state **hash_tab)
{
	printf("Complexity in Time (States selected) = %u \n", data->com_time);
	printf("Complexity in Size  (States in memory) = %u \n", data->com_size);
	file_print(data->cur, data);
	free_n_all(data, hash_tab, heap);
}

static void	new_n_state(t_puzzle_data *data, t_heap *heap,
		uint64_t id_successor, t_state **hash_tab)
{
	t_state		*successor;

	data->com_size++;
	successor = mem_state_n(id_successor, data->su_coor,
			data->cur, data);
	successor->cost = data->cur->cost + data->search_cost;
	push_heap(heap, successor);
	add_node(&hash_tab[hash_table_n(successor->coor,
				successor->value, data->area)], successor);
}

static void	update_n_state(t_puzzle_data *data, t_heap *heap,
		t_state *successor)
{
	successor->pre = data->cur;
	successor->cost = data->cur->cost + data->search_cost;
	if (!successor->i_heap)
		push_heap(heap, successor);
	else
		up_heap(heap, successor->i_heap);
}

static void	move_n_tile(t_puzzle_data *data, t_heap *heap, t_state **hash_tab)
{
	uint64_t		id_successor;
	int				i;
	t_state			*successor;

	i = -1;
	while (++i < 4)
	{
		if ((id_successor = data->move_n[i](data->cur, data->su_coor,
						data->su_val, data->size)))
		{
			if (!(successor = search_node_n(hash_tab[
						hash_table_n(data->su_coor, data->su_val, data->area)],
						id_successor, data->su_coor, data->area)))
				new_n_state(data, heap, id_successor, hash_tab);
			else if (successor->cost > data->cur->cost +
					data->search_cost)
				update_n_state(data, heap, successor);
		}
	}
}

void		start_a_n(t_heap *heap, uint64_t id_goal, t_state **hash_tab,
		t_puzzle_data *data)
{
	int				success;

	data->su_coor = puz_alloc(data->area);
	data->su_val = puz_alloc(data->area);
	success = 0;
	while (heap->size > 0 && !success)
	{
		data->com_time++;
		data->cur = pop_heap(heap);
		if (data->cur->id == id_goal && same_state(data->cur->coor,
					data->goal_coor, data->area))
			success = 1;
		else
			move_n_tile(data, heap, hash_tab);
	}
	ft_memdel((void**)&data->su_coor);
	ft_memdel((void**)&data->su_val);
	display_n_result(data, heap, hash_tab);
}
