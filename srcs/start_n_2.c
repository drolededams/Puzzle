/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_n_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 14:48:20 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/28 14:48:50 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

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

void		free_n_all(t_puzzle_data *data, t_state **hash_tab, t_heap *heap)
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
