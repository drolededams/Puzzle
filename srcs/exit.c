/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:37:40 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/27 19:59:05 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

void	exit_bad_file(char **line, char **split, t_puzzle_data *data, int code)
{
	if (code == SIZES)
		ft_putendl("One size is enough:");
	else if (code == TOO_LOW)
		ft_putendl("The size must be >= 2 and <=5:");
	else if (code == NO_SIZE)
		ft_putendl("Size missing or not enough numbers in a line or too much l\
ine:");
	if (*line)
	{
		ft_putendl(*line);
		ft_memdel((void**)line);
	}
	if (split)
		free_tab(split);
	if (data->size > 1 && data->size < 6)
		ft_memdel((void**)&data->puzzle);
	ft_memdel((void**)&data);
	exit(0);
}

void	exit_bad_file2(t_puzzle_data *data)
{
	if (!data->line)
		ft_putendl("Bad file");
	else
	{
		ft_putendl("Not enough line");
		if (data->size != 0)
			ft_memdel((void**)&data->puzzle);
	}
	ft_memdel((void**)&data);
	exit(0);
}

void	exit_bad_line(char *line, t_puzzle_data *data, int code)
{
	if (code == BAD_LINE)
		ft_putendl("Bad line in the file:");
	if (line)
	{
		ft_putendl(line);
		ft_memdel((void**)&line);
	}
	if (data->size != 0)
		ft_memdel((void**)&data->puzzle);
	ft_memdel((void**)&data);
	exit(0);
}

void	exit_alloc_failed(void)
{
	ft_putendl("memory allocation failed");
	exit(0);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_memdel((void**)&tab[i]);
		i++;
	}
	ft_memdel((void**)&tab[i]);
	ft_memdel((void*)&tab);
}

void	free_tab_int(int **tab, int area)
{
	int i;

	i = 0;
	while (i < area)
	{
		ft_memdel((void**)&tab[i]);
		i++;
	}
	ft_memdel((void**)&tab[i]);
	ft_memdel((void*)&tab);
}

void	exit_bad_puzzle(t_puzzle_data *data, int code)
{
	if (code == NUMBER_MISSING)
		ft_putendl("Number missing in the N-Puzzle.");
	else if (code == IMPOSSIBLE)
	{
		ft_putendl("The N-Puzzle can't be solved.");
		ft_memdel((void**)&data->state_coor);
		ft_memdel((void**)&data->goal_coor);
		ft_memdel((void**)&data->goal_value);
		ft_memdel((void**)&data->puzzle);
	}
	if (data->size != 0)
		ft_memdel((void**)&data->puzzle);
	ft_memdel((void**)&data);
	exit(0);
}
