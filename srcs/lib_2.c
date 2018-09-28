/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 14:32:51 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/28 14:44:04 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

int				move_count(t_state *state)
{
	int		move;
	t_state *cpy;

	move = -1;
	cpy = state;
	while (cpy != NULL)
	{
		move++;
		cpy = cpy->pre;
	}
	return (move);
}

void			swap_tabint(unsigned int *tab, int a, int b)
{
	unsigned int tmp;

	tmp = tab[a];
	tab[a] = tab[b];
	tab[b] = tmp;
}
