/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:06:27 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/26 16:45:12 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

char			*file_name(t_puzzle_data *data)
{
	uint64_t	id_begin;
	int			r;
	int			i;
	char		*name;

	if (!(name = (char*)malloc(sizeof(char) * 24)))
		exit_alloc_failed();
	i = 0;
	id_begin = id_state(data->state_coor, data->area);
	while (id_begin)
	{
		r = id_begin % 10;
		name[i] = r + 48;
		id_begin /= 10;
		i++;
	}
	while (i < 20)
	{
		name[i] = 'x';
		i++;
	}
	name[i] = '_';
	if (!data->search_cost)
		name[i + 1] = 'g';
	else if (!data->heu_choice)
		name[i + 1] = 'u';
	else
		name[i + 1] = 'a';
	name[i + 2] = data->heu_choice + 48;
	name[i + 3] = '\0';
	return (name);
}

int				move_count(t_state *state)
{
	int		move;
	t_state *cpy;

	move = -1;
	cpy = state;
	while (cpy != NULL)
	{
		move++;
		cpy = cpy->pre;
	}
	return (move);
}

unsigned int	**state_sort(t_state *state, int n)
{
	unsigned int **tab;

	if (!(tab = (unsigned int**)malloc(sizeof(unsigned int*) * n + 1)))
		exit_alloc_failed();
	while (state != NULL)
	{
		tab[n] = state->coor;
		state = state->pre;
		n--;
	}
	return (tab);
}

void			file_print(t_state *state, t_puzzle_data *data)
{
	FILE			*file;
	char			*name;
	unsigned int	**print;
	int				move;
	int				i;

	file = NULL;
	name = file_name(data);
	file = fopen(name, "w+");
	i = 0;
	if (!data->search_cost)
		move = move_count(state);
	else
		move = state->cost;
	print = state_sort(state, move);
	if (file != NULL)
	{
		while (i < move)
		{
			fprint_coor(file, print[i], data->area);
			fprintf(file, "\n\n");
			i++;
		}
		fprint_coor(file, print[i], data->area);
		fclose(file);
	}
	else
	{
		ft_putendl("Error : file can't be open");
		while (i < move)
		{
			print_coor(print[i], data->area);
			printf("\n\n");
			i++;
		}
		print_coor(print[i], data->area);
	}
	printf("Number of Moves = %d \n", move);
	ft_memdel((void**)&print);
	ft_memdel((void**)&name);
}
