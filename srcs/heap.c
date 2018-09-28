/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:33:34 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/28 14:36:44 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

void		push_heap(t_heap *heap, t_state *state)
{
	heap->size++;
	if (heap->size >= heap->max)
		realloc_heap(heap);
	heap->tab[heap->size] = state;
	state->i_heap = heap->size;
	if (heap->size != 1)
		up_heap(heap, heap->size);
}

void		up_heap(t_heap *heap, int i)
{
	int		father;
	int		i_heap_tmp;
	t_state	*s_tmp;

	father = i >> 1;
	while (i > 1 && heap->tab[father]->cost + heap->tab[father]->heu >
			heap->tab[i]->cost + heap->tab[i]->heu)
	{
		i_heap_tmp = heap->tab[father]->i_heap;
		heap->tab[father]->i_heap = heap->tab[i]->i_heap;
		heap->tab[i]->i_heap = i_heap_tmp;
		s_tmp = heap->tab[father];
		heap->tab[father] = heap->tab[i];
		heap->tab[i] = s_tmp;
		i = father;
		father = father >> 1;
	}
}

t_state		*pop_heap(t_heap *heap)
{
	t_state *best;

	if (!heap->size)
		return (NULL);
	best = heap->tab[1];
	best->i_heap = 0;
	if (heap->size != 1)
	{
		heap->tab[1] = heap->tab[heap->size];
		heap->tab[1]->i_heap = 1;
	}
	else
		heap->tab[1] = NULL;
	heap->size--;
	if (heap->size)
		down_heap(heap);
	return (best);
}

void		down_heap(t_heap *heap)
{
	t_state *tmp;
	int		i_up;
	int		i_down;

	i_up = 1;
	i_down = 2;
	while (i_down <= heap->size)
	{
		if (i_down + 1 <= heap->size && heap->tab[i_down]->cost +
				heap->tab[i_down]->heu > heap->tab[i_down + 1]->cost +
				heap->tab[i_down + 1]->heu)
			i_down++;
		if (heap->tab[i_down]->cost + heap->tab[i_down]->heu <
				heap->tab[i_up]->cost + heap->tab[i_up]->heu)
		{
			heap->tab[i_down]->i_heap = i_up;
			heap->tab[i_up]->i_heap = i_down;
			tmp = heap->tab[i_down];
			heap->tab[i_down] = heap->tab[i_up];
			heap->tab[i_up] = tmp;
		}
		i_up = i_down;
		i_down = i_down << 1;
	}
}
