/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:47:13 by dgameiro          #+#    #+#             */
/*   Updated: 2018/02/26 20:15:20 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	print_puzzle(int *tab, int n)
{
	int i;
	int j;
	int sqrt;

	i = -1;
	j = 0;
	sqrt = ft_sqrt(n);
	while (++i < n)
	{
		while (j++ < sqrt - 1)
		{
			ft_putnbr(tab[i++]);
			ft_putchar(' ');
		}
		ft_putnbr(tab[i]);
		ft_putchar('\n');
		j = 0;
	}
}

void	print_coor(int *tab, int n)
{
	int *puz;
	int i;

	if (!(puz = (int*)malloc(sizeof(int) * n)))
		exit_alloc_failed(); //liberation memoire a faire
	i = -1;
	while (++i < n)
		puz[tab[i]] = i;
	print_puzzle(puz, n);
	ft_memdel((void*)&puz);
}
