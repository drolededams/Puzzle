/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:42:36 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/26 14:00:01 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
static int li = 0;
#include "N-Puzzle.h"

void	get_file(char *file, t_puzzle_data *data)
{
	int		fd;
	char	*line;

	if ((fd = open(file, O_RDONLY)) != -1)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (line)
			{
				if (good_line(line))
					analyse_line(line, data);
				else
					exit_bad_line(&line, data, BAD_LINE);
				ft_memdel((void**)&line);
			}
			li++;
		}
		close(fd);
	}
	if (!data->line || data->line != data->size)
		exit_bad_file2(data);
}

int		good_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '#')
			return (1);
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			return (0);
		i++;
	}
	return (i);
}

void	analyse_line(char *line, t_puzzle_data *data)
{
	char	**split;
	int		i;

	split = strcomsplit(line, ' '); //leaks
	if (split == NULL)
	{
		return ;
	}
	if (split[1] == NULL)
	{
		if (data->size != 0)
			exit_bad_file(&line, split, data, SIZES); // 2 fois la taille
		else if ((data->size = ft_atoi(split[0])) < 2)
			exit_bad_file(&line, split, data, TOO_LOW);// taille n puzzle trop petit
		data->area = data->size * data->size;
		free_tab(split);
		mem_puzzle(data);
	}
	else if (data->size != 0 && mat_len_y(split) == data->size && data->size > data->line)
	{
		i = -1;
		while (split[++i])
			data->puzzle[data->line * data->size + i] = ft_atoi(split[i]);
		data->line++;
		free_tab(split);
	}
	else
		exit_bad_file(&line, split, data, NO_SIZE); //pas de taille de tableau || pas assez de chiffre sur la ligne || trop de ligne
}
