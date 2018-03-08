/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:47:13 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/07 18:13:03 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	print_puzzle(unsigned int *tab, int n)
{
	int i;
	int j;
	int k;
	int u;
	int cpy;
	int sqrt;

	i = -1;
	j = 0;
	k = 0;
	sqrt = ft_sqrt(n);
	cpy = n;
	u = decimal_number(n);
	k = 0;
	while (++i < n)
	{
		while (j++ < sqrt - 1)
		{
			k = decimal_number(tab[i]);
			while (k != u)
			{
				printf(" ");
				k++;
			}
			printf("%u ", tab[i++]);
		}
		printf("%u\n", tab[i]);
		j = 0;
	}
}

void	print_coor(unsigned int *tab, int n)
{
	unsigned int	*puz;
	int				i;

	if (!(puz = (unsigned int*)malloc(sizeof(unsigned int) * n)))
		exit_alloc_failed(); //liberation memoire a faire
	i = -1;
	while (++i < n)
		puz[tab[i]] = i;
	print_puzzle(puz, n);
	ft_memdel((void*)&puz);
}

void	fprint_coor(FILE *fichier, unsigned int *tab, int n)
{
	unsigned int *puz;
	int i;

	if (!(puz = (unsigned int*)malloc(sizeof(unsigned int) * n)))
		exit_alloc_failed(); //liberation memoire a faire
	i = -1;
	while (++i < n)
		puz[tab[i]] = i;
	fprint_puzzle(fichier, puz, n);
	ft_memdel((void*)&puz);
}

void	fprint_puzzle(FILE *fichier, unsigned int *tab, int n)
{
	int i;
	int j;
	int k;
	int u;
	int cpy;
	int sqrt;

	i = -1;
	j = 0;
	k = 0;
	sqrt = ft_sqrt(n);
	cpy = n;
	u = decimal_number(n);
	k = 0;
	while (++i < n)
	{
		while (j++ < sqrt - 1)
		{
			k = decimal_number(tab[i]);
			while (k != u)
			{
				fprintf(fichier, " ");
				k++;
			}
			fprintf(fichier, "%u ", tab[i++]);
		}
		k = decimal_number(tab[i]);
		while (k != u)
		{
			fprintf(fichier, " ");
			k++;
		}
		fprintf(fichier, "%u\n", tab[i]);
		j = 0;
	}
}

int		decimal_number(int n)
{
	int d;

	d = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		d++;
	}
	return (d);
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
	uint64_t	maxpow;
	int			i;
	int			j;

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
