/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:06:27 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/27 19:59:05 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

char			*file_name(t_puzzle_data *data)
{
	int		len;
	char	*str;

	len = ft_strlen("result");
	if (!(str = malloc(sizeof(char) * (len + 4))))
		exit_alloc_failed();
	ft_strcpy(str, "result");
	str[len] = '_';
	if (!data->search_cost)
		str[len + 1] = 'g';
	else if (!data->heu_choice)
		str[len + 1] = 'u';
	else
		str[len + 1] = 'a';
	str[len + 2] = data->heu_choice + 48;
	str[len + 3] = '\0';
	return (str);
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

static void		file_solution(FILE *file, unsigned int **print, int move,
		t_puzzle_data *data)
{
	int				i;

	i = 0;
	while (i < move)
	{
		fprint_coor(file, print[i], data);
		fprintf(file, "\n\n");
		i++;
	}
	fprint_coor(file, print[i], data);
	fclose(file);
}

static void		print_solution(unsigned int **print, int move,
		t_puzzle_data *data)
{
	int i;

	i = 0;
	ft_putendl("Error : file can't be open");
	while (i < move)
	{
		print_coor(print[i], data);
		printf("\n\n");
		i++;
	}
	print_coor(print[i], data);
}

void			file_print(t_state *state, t_puzzle_data *data)
{
	FILE			*file;
	char			*name;
	unsigned int	**print;
	int				move;

	file = NULL;
	name = file_name(data);
	file = fopen(name, "w+");
	if (!data->search_cost)
		move = move_count(state);
	else
		move = state->cost;
	print = state_sort(state, move);
	if (file != NULL)
		file_solution(file, print, move, data);
	else
		print_solution(print, move, data);
	printf("Number of Moves = %d \n", move);
	ft_memdel((void**)&print);
	ft_memdel((void**)&name);
}
