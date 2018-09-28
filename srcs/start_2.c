/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 14:51:58 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/28 14:53:26 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

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

void		free_all(t_puzzle_data *data, t_state **hash_tab, t_heap *heap)
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
