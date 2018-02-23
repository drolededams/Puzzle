/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 12:03:29 by dgameiro          #+#    #+#             */
/*   Updated: 2018/02/23 18:14:36 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	generation(t_puzzle_data *data)
{
	char *line;

	ft_putendl("Renseignez la taille du N-Puzzle (Max : x):");
	get_next_line(STDIN_FILENO, &line);
	if((data->size = size_verif(line)))
	{
		ft_memdel((void**)&line);
		srand(time(NULL));
		coor_alloc(data);
		func_init(data);
		make_npuzzle(data);
	}
	else
	{
		ft_memdel((void**)&line);
		generation(data);
	}
}

void	make_npuzzle(t_puzzle_data *data)
{
	int *randtab;
	int i;

	if(!(randtab = (int*)malloc(sizeof(int) * data->size * data->size)))
		exit_alloc_failed(); //liberation memoire a faire
	i = -1;
	while (++i < data->size * data->size)
		randtab[i] = i;
	random_tab(randtab, data->size * data->size);
	print_tabint(randtab, data->size * data->size);
	random_is_soluble(data, randtab);
}

void	random_is_soluble(t_puzzle_data *data, int *tab)
{
	int i;
	int blank_dis;
	int permutation;
	
	i = -1;
	while (++i < data->size * data->size)
	{
		data->state_coor[tab[i]] = coor_modulo(i, data->size);
		data->goal_coor[i] = find_final_coor(data, i);
	}
	blank_dis = distance(data->state_coor[0], data->goal_coor[0]) % 2;
	permutation = permutation_calc(data) % 2;

	if (blank_dis == permutation)
		ft_putendl("Puzzle Soluble");
	else
	{
		ft_memdel((void**)&tab);
		ft_putendl("Puzzle Non Soluble. Generation d'un nouveau");
		make_npuzzle(data);
	}
}

t_coor	coor_modulo(int i, int n)
{
	t_coor coor;

	coor.y = i % n;
	coor.x = i / n;
	return(coor);
}


void print_tabint(int *tab, int n)
{
	int i;

	i = -1;
	while(++i < n)
	{
		ft_putnbr(tab[i]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}

void	random_tab(int *randtab, int n)
{
	int i;

	i = -1;
	while (++i < n)
		swap_tabint(randtab, i, rand()%n);
}

void swap_tabint(int *tab, int a, int b)
{
	int tmp;

	tmp = tab[a];
	tab[a] = tab[b];
	tab[b] = tmp;
}

int size_verif(char *s)
{
	if(!is_num(s))
	{
		ft_putendl("Caractères numériques seulement. Max : x");
		return (0);
	}
	if (ft_strlen(s) > 2)
	{
		ft_putendl("La taille doit 2 < n <= 15");
		return (0);
	}
	if (ft_atoi(s) < 2 || ft_atoi(s) > 15)
	{
		ft_putendl("La taille doit 2 < n <= 15");
		return (0);
	}
	return (ft_atoi(s));
}

int		is_num(char *s)
{
	int i;

	i = 0;
	while(s[i])
		if (!ft_isdigit(s[i++]))
			return (0);
	return (i);
}
