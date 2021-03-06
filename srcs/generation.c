/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 12:03:29 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/27 19:59:06 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

void	generation(t_puzzle_data *data)
{
	char	*line;
	int		rep;

	ft_putendl("Renseignez la taille du N-Puzzle (Max : 5):");
	if ((rep = get_next_line(STDIN_FILENO, &line)) > 0 &&
			(data->size = size_verif(line)))
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
		if (rep > 0)
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
		ft_putendl("La taille doit 2 <= n <= 5");
		return (0);
	}
	if (ft_atoi(s) < 2 || ft_atoi(s) > 5)
	{
		ft_putendl("La taille doit 2 <= n <= 5");
		return (0);
	}
	return (ft_atoi(s));
}
