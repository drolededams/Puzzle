/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 10:49:05 by dgameiro          #+#    #+#             */
/*   Updated: 2018/02/26 18:04:11 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

int		main(int ac, char **av)
{
	t_puzzle_data	*data;
	int				i;
	int				j;

	if (!(data = (t_puzzle_data*)malloc(sizeof(t_puzzle_data))))
		exit_alloc_failed();
	data->size = 0;
	data->line = 0;
	i = 0;
	j = 0;
	if (ac == 2)
	{
		get_file(av[1], data);
		print_puzzle(data->puzzle, data->size * data->size);
		verif_puzzle(data);
	}
	else if (ac == 1)
		generation(data);
	else
	{
		ft_memdel((void**)data);
		ft_putstr("usage: ./N-Puzzle file (max one file)\n");
	}
	return (1);
}
