/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 10:49:05 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/27 19:59:06 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

int		main(int ac, char **av)
{
	t_puzzle_data	*data;

	if (!(data = (t_puzzle_data*)malloc(sizeof(t_puzzle_data))))
		exit_alloc_failed();
	data->size = 0;
	data->line = 0;
	if (ac == 2)
	{
		get_file(av[1], data);
		verif_puzzle(data);
	}
	else if (ac == 1)
		generation(data);
	else
	{
		ft_memdel((void**)&data);
		ft_putstr("usage: ./N-Puzzle file (max one file)\n");
	}
	return (1);
}
