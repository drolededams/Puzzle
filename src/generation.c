/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 12:03:29 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/06 12:59:22 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	generation(t_puzzle_data *data)
{
	char	*line;

	ft_putendl("Renseignez la taille du N-Puzzle (Max : x):");
	get_next_line(STDIN_FILENO, &line);
	if ((data->size = size_verif(line)))
	{
		ft_memdel((void**)&line);
		srand(time(NULL));
		data->area = data->size * data->size;
		coor_alloc(data);
		func_init(data);
		mem_puzzle(data);
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
	unsigned int i;

	i = 0;
	while (i < data->area)
	{
		data->puzzle[i] = i;
		i++;
	}
	random_tab(data->puzzle, data->area);
	is_soluble(data, 1);
}

void	random_tab(unsigned int *tab, int n)
{
	int i;

	i = -1;
	while (++i < n)
		swap_tabint(tab, i, rand() % n);
}

int		size_verif(char *s)
{
	if (!is_num(s))
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
