/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:06:27 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/19 18:40:14 by dgameiro         ###   ########.fr       */
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
	printf("The sequence is saved in file : %s\n", name);
	ft_memdel((void**)&name);
}

uint64_t *pb_tab(void)
{
	uint64_t *tab;
	uint64_t n;
	unsigned int i;
	unsigned int j;
	char *line;
	int fd;

	if (!(tab = (uint64_t*)malloc(sizeof(uint64_t) * 116)))
		exit_alloc_failed();
	i = 0;
	j = 0;
	if((fd = open("table", O_RDONLY)) != -1)
	{
		while(get_next_line(fd, &line) > 0)
		{
			if(line)
			{
				i = 0;
				n = 0;
				while(line[i + 1])
				{
					n += line[i] - 48;
					n *= 10;
					i++;
				}
				n += line[i] - 48;
				tab[j] = n;
				j++;
				ft_memdel((void**)&line);
			}
		}
		close(fd);
	}
	return (tab);
}

int  is_ontab(uint64_t *tab, uint64_t n)
{
	int i;

	i = 0;
	while (i < 116)
	{
		if (n == tab[i])
			return (i + 1);
		i++;
	}
	return (0);
}
