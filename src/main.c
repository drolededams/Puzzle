/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 10:49:05 by dgameiro          #+#    #+#             */
/*   Updated: 2018/02/21 19:44:54 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	get_file(char *file, t_puzzle_data *data)
{
	int fd;
	char *line;

	if((fd = open(file, O_RDONLY)) != -1)
	{
		while(get_next_line(fd, &line) > 0)
		{
			if (line)
			{
				if(good_line(line))
					analyse_line(line, data);
				else
					exit_bad_file(&line, data, BAD_LINE);
				ft_memdel((void**)&line);
			}
		}
	}
	if(!data->line || data->line != data->size)
	{
		ft_putstr("Bad file\n");
		ft_memdel((void**)&data);
		exit(0);
	}
}

int		good_line(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if (line[i] == '#')
			return 1;
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			return 0;
		i++;
	}
	return i;
}

void	analyse_line(char *line, t_puzzle_data *data)
{
	char **tab;
	int i;

	tab = strcomsplit(line, ' ');
	if(tab[0] == NULL)
		return; 
	if (tab[1] == NULL)
	{
		if (data->size != 0)
		{
			free_tab(tab);
			exit_bad_file(&line, data, SIZES); // 2 fois la taille
		}
		else if ((data->size = ft_atoi(tab[0])) < 2)
		{
			free_tab(tab);
			exit_bad_file(&line, data, TOO_LOW);// taille n puzzle trop petit
		}
		mem_puzzle(data);
	}
	else if (data->size != 0 && tablen(tab) == data->size && data->size > data->line)
	{
		i = 0;
		while(tab[i])
		{
			data->puzzle[data->line][i] = ft_atoi(tab[i]);
			i++;
		}
		data->line++;
		free_tab(tab);
	}
	else
	{
		free_tab(tab);
		exit_bad_file(&line, data, NO_SIZE); //pas de taille de tableau || pas assez de chiffre sur la ligne || trop de ligne
	}
}

int		tablen(char **tab)
{
	int i;

	i = 0;
	while(tab[i] != NULL)
		i++;
	return i;
}

void	mem_puzzle(t_puzzle_data *data)
{
	int i;

	i = 0;
	if(!(data->puzzle = (int**)malloc(sizeof(int*) * data->size)))
		exit_alloc_failed();
	while(i < data->size)
		if(!(data->puzzle[i++] = (int*)malloc(sizeof(int) * data->size)))
			exit_alloc_failed();
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		ft_memdel((void**)&tab[i]);
		i++;
	}
	ft_memdel((void**)&tab[i]);
	ft_memdel((void**)tab);
}

void	exit_bad_file(char **line, t_puzzle_data *data, int code)
{
	if(code == BAD_LINE)
		ft_putstr("Bad line in the file:\n");
	else if (code == SIZES)
		ft_putstr("One size is enough:\n");
	else if (code == TOO_LOW)
		ft_putstr("The size must be >= 2:\n");
	else if (code == NO_SIZE)
		ft_putstr("Size missing or not enough numbers in a line or too much line:\n");
	if(*line)
		ft_putendl(*line);
	ft_memdel((void**)line);
	ft_memdel((void**)&data);
	exit(0);
}

void	exit_alloc_failed(void)
{
	ft_putstr("memory allocation failed\n");
	exit(0);
}

int		main (int ac, char** av)
{
	
	t_puzzle_data *data;
	int i;
	int j;

	if(!(data = (t_puzzle_data*)malloc(sizeof(t_puzzle_data))))
		exit_alloc_failed();
	data->size = 0;
	data->line = 0;
	i = 0;
	j = 0;
	if(ac == 2)
	{
		get_file(av[1], data);
		while(i < data->size)
		{
			while (j < data->size)
				printf("%d ", data->puzzle[i][j++]);
			printf("\n");
			j = 0;
			i++;
		}
		//verif_puzzle(data);
	}
	else if (ac  == 1)
		ft_putstr("Génération du puzzle\n");
	else
	{
		ft_memdel((void**)data);
		ft_putstr("usage: ./N-Puzzle file (max one file)\n");
	}
	return (1);
}
