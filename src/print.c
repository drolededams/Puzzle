/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:47:13 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/26 17:04:26 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	print_puzzle(unsigned int *tab, int n)
{
	int i;
	int j;
	int k;
	int u;
	int sqrt;

	i = -1;
	j = 0;
	k = 0;
	sqrt = ft_sqrt(n);
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
		exit_alloc_failed();
	i = -1;
	while (++i < n)
		puz[tab[i]] = i;
	print_puzzle(puz, n);
	ft_memdel((void*)&puz);
}

void	fprint_coor(FILE *fichier, unsigned int *tab, int n)
{
	unsigned int	*puz;
	int				i;

	if (!(puz = (unsigned int*)malloc(sizeof(unsigned int) * n)))
		exit_alloc_failed();
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
	int sqrt;

	i = -1;
	j = 0;
	k = 0;
	sqrt = ft_sqrt(n);
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
