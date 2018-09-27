/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:30:22 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/27 19:05:29 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void		free_tree(t_state *node)
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

void		pre_start_a(t_puzzle_data *data)
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
	data->com_size = 1;
	data->com_time = 0;
	start_a(heap, id_goal, hash_tab, data);
}

static void	free_all(t_puzzle_data *data, t_state **hash_tab, t_heap *heap)
{
	int i;

	ft_memdel((void**)&data->state_coor);
	ft_memdel((void**)&data->goal_coor);
	ft_memdel((void**)&data->goal_value);
	ft_memdel((void**)&data->puzzle);
	free_heap(heap);
	i = 0;
	while (i < 1024)
	{
		free_tree(hash_tab[i]);
		i++;
	}
	ft_memdel((void**)&hash_tab);
	ft_memdel((void**)&data);
}

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
	printf("Complexity in Time (States selected) = %d \n", data->com_time);
	printf("Complexity in Size  (States in memory) = %d \n", data->com_size);
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
