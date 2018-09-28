/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 14:35:24 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/28 14:37:11 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

t_heap		*mem_heap(void)
{
	t_heap	*heap;

	if (!(heap = (t_heap*)malloc(sizeof(t_heap))))
		exit_alloc_failed();
	heap->max = 524288;
	if (!(heap->tab = (t_state**)malloc(sizeof(t_state*) * heap->max)))
		exit_alloc_failed();
	heap->size = 0;
	return (heap);
}

void		realloc_heap(t_heap *heap)
{
	t_state **tmp;

	heap->max = heap->max << 1;
	if (!(tmp = (t_state**)realloc(heap->tab, sizeof(t_state*) * heap->max)))
		exit_alloc_failed();
	else
		heap->tab = tmp;
}

void		free_heap(t_heap *heap)
{
	free(heap->tab);
	free(heap);
}
