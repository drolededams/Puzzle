/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:30:22 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/01 19:21:08 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	start_a(t_puzzle_data *data)
{
	t_state	*start;
	t_heap	*heap;
	unsigned int size;

	size = data->size * data->size;
	start = mem_state_4(id_state(data->state_coor, size), NULL, size, data->goal_coor);
	heap = mem_heap();
	push_heap(heap, start);
	ft_putendl("yes ?");
	print_coor(heap->tab[1]->value, size);
}
