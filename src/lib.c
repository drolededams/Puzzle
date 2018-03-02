/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:43:42 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/02 15:53:22 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	swap_tabint(unsigned int *tab, int a, int b)
{
	unsigned int tmp;

	tmp = tab[a];
	tab[a] = tab[b];
	tab[b] = tmp;
}

void	func_init(t_puzzle_data *data)
{
	data->coor[0] = coor_top;
	data->coor[1] = coor_right;
	data->coor[2] = coor_bottom;
	data->coor[3] = coor_left;
}

int		is_num(char *s)
{
	int i;

	i = 0;
	while (s[i])
		if (!ft_isdigit(s[i++]))
			return (0);
	return (i);
}

int		mat_len_y(char **mat)
{
	int i;

	i = 0;
	while (mat[i] != NULL)
		i++;
	return (i);
}

unsigned int		*tab_copy(unsigned int *tab, int size)
{
	unsigned int *copy;
	int i;

	if (!(copy = (unsigned int*)malloc(sizeof(unsigned int) * size)))
		exit_alloc_failed();//mem a lib
	i = -1;
	while (++i < size)
		copy[i] = tab[i];
	return (copy);
}
