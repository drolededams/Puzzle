/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:47:13 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/02 15:53:14 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	print_puzzle(unsigned int *tab, int n)
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

void	print_coor(unsigned int *tab, int n)
{
	unsigned int *puz;
	int i;

	if (!(puz = (unsigned int*)malloc(sizeof(unsigned int) * n)))
		exit_alloc_failed(); //liberation memoire a faire
	i = -1;
	while (++i < n)
		puz[tab[i]] = i;
	print_puzzle(puz, n);
	ft_memdel((void*)&puz);
}

void	print_tabint(unsigned int *tab, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		ft_putnbr(i);
		ft_putstr(" = ");
		ft_putnbr(tab[i++]);
		ft_putstr(" | ");
	}
		ft_putchar('\n');
}

void		print_bits(uint64_t n)
{
	uint64_t maxpow;
	int i;
	int j;

	maxpow = 1 << 31;
	maxpow = maxpow << 31;
	maxpow = maxpow << 1;
	i = 0;
	j = 0;
	printf("%" PRIu64 "\n", n);
	while (i < 64)
	{
		while (j < 4)
		{
			printf("%u ", !!(n & maxpow));
			i++;
			j++;
			n = n << 1;
		}
		printf("\n");
		j = 0;
	}
}
