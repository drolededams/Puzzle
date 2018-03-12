/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:33:34 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/09 17:29:35 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

t_heap		*mem_heap(void)
{
	t_heap	*heap;

	if (!(heap = (t_heap*)malloc(sizeof(t_heap))))
		exit_alloc_failed();
	H_MAX = 524288;
	if (!(heap->tab = (t_state**)malloc(sizeof(t_state*) * H_MAX)))
		exit_alloc_failed();
	H_SIZE = 0;
	return (heap);
}

void		realloc_heap(t_heap *heap)
{
	t_state **tmp;

	H_MAX = H_MAX << 1;
	if (!(tmp = (t_state**)realloc(heap->tab, sizeof(t_state*) * H_MAX)))
		exit_alloc_failed();
	else
		heap->tab = tmp;
}//fonctions a test

void		push_heap(t_heap *heap, t_state *state)
{
	H_SIZE++;
	if (H_SIZE >= H_MAX)
		realloc_heap(heap);
	H_LAST = state;
	state->i_heap = H_SIZE;
	if (H_SIZE != 1)
		up_heap(heap, H_SIZE);
}

void		up_heap(t_heap *heap, int i)
{
	int		father;
	int		i_heap_tmp;
	t_state	*s_tmp;

	father = i >> 1;
	while (i > 1 && H_FATH_F > H_I_F)
	{
		i_heap_tmp = H_FATH_IH;
		H_FATH_IH = H_I_IH;
		H_I_IH = i_heap_tmp;
		s_tmp = H_FATH;
		H_FATH = H_I;
		H_I = s_tmp;
		i = father;
		father = father >> 1;
	}
}

t_state		*pop_heap(t_heap *heap)
{
	t_state *best;

	if (!H_SIZE)
		return (NULL);
	best = heap->tab[1];
	best->i_heap = 0;
	if(H_SIZE != 1)
	{
		heap->tab[1] = H_LAST;
		heap->tab[1]->i_heap = 1;
	}
	else
		heap->tab[1] = NULL;
	H_SIZE--;
	if (H_SIZE)
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
	while (i_down <= H_SIZE)
	{
		if (i_down + 1 <= H_SIZE && H_DOWN_F > H_DOWN_1_F)
			i_down++;
		if (H_DOWN_F < H_UP_F)
		{
			H_DOWN_IH = i_up;
			H_UP_IH = i_down;
			tmp = H_DOWN;
			H_DOWN = H_UP;
			H_UP = tmp;
		}
		i_up = i_down;
		i_down = i_down << 1;
	}
}

void		free_heap(t_heap *heap)
{
	ft_memdel((void**)&heap->tab);
	ft_memdel((void**)&heap);
}
