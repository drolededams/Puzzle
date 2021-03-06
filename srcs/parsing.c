/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:42:36 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/27 19:59:05 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

void		get_file(char *file, t_puzzle_data *data)
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
					exit_bad_line(line, data, BAD_LINE);
				ft_memdel((void**)&line);
			}
		}
		close(fd);
	}
	if (!data->line || data->line != data->size)
		exit_bad_file2(data);
}

int			good_line(char *line)
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

static void	fill_line(t_puzzle_data *data, char **split)
{
	int		i;

	i = -1;
	while (split[++i])
		data->puzzle[data->line * data->size + i] = ft_atoi(split[i]);
	data->line++;
	free_tab(split);
}

void		analyse_line(char *line, t_puzzle_data *data)
{
	char	**split;

	split = strcomsplit(line, ' ');
	if (split == NULL)
		return ;
	if (split[1] == NULL)
	{
		if (data->size != 0)
			exit_bad_file(&line, split, data, SIZES);
		else if ((data->size = ft_atoi(split[0])) < 2 || data->size > 5)
			exit_bad_file(&line, split, data, TOO_LOW);
		data->area = data->size * data->size;
		free_tab(split);
		mem_puzzle(data);
	}
	else if (data->size != 0 && mat_len_y(split) == data->size &&
			data->size > data->line)
		fill_line(data, split);
	else
		exit_bad_file(&line, split, data, NO_SIZE);
}
