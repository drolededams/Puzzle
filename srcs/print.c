/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:47:13 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/27 15:39:47 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void			print_puzzle(unsigned int *tab, t_puzzle_data *data)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;
	unsigned int u;

	i = 0;
	k = 0;
	u = decimal_number(data->area);
	while (i < data->area)
	{
		j = 0;
		while (j++ < data->size - 1)
		{
			k = decimal_number(tab[i]);
			while (k++ != u)
				printf(" ");
			printf("%u ", tab[i++]);
		}
		k = decimal_number(tab[i]);
		while (k++ != u)
			printf(" ");
		printf("%u\n", tab[i]);
		i++;
	}
}

void			print_coor(unsigned int *tab, t_puzzle_data *data)
{
	unsigned int	*puz;
	unsigned int	i;

	if (!(puz = (unsigned int*)malloc(sizeof(unsigned int) * data->area)))
		exit_alloc_failed();
	i = 0;
	while (i < data->area)
	{
		puz[tab[i]] = i;
		i++;
	}
	print_puzzle(puz, data);
	ft_memdel((void*)&puz);
}

void			fprint_coor(FILE *fichier, unsigned int *tab,
		t_puzzle_data *data)
{
	unsigned int	*puz;
	unsigned int	i;

	if (!(puz = (unsigned int*)malloc(sizeof(unsigned int) * data->area)))
		exit_alloc_failed();
	i = 0;
	while (i < data->area)
	{
		puz[tab[i]] = i;
		i++;
	}
	fprint_puzzle(fichier, puz, data);
	ft_memdel((void*)&puz);
}

void			fprint_puzzle(FILE *fichier, unsigned int *tab,
		t_puzzle_data *data)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;
	unsigned int u;

	i = 0;
	k = 0;
	u = decimal_number(data->area);
	while (i < data->area)
	{
		j = 0;
		while (j++ < data->size - 1)
		{
			k = decimal_number(tab[i]);
			while (k++ != u)
				fprintf(fichier, " ");
			fprintf(fichier, "%u ", tab[i++]);
		}
		k = decimal_number(tab[i]);
		while (k++ != u)
			fprintf(fichier, " ");
		fprintf(fichier, "%u\n", tab[i]);
		i++;
	}
}

unsigned int	decimal_number(unsigned int n)
{
	unsigned int d;

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
