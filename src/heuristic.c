/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:06:10 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/14 16:30:33 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

unsigned int	hamming_dist(unsigned int *state, t_puzzle_data *data)
{
	unsigned int i;
	unsigned int heu;

	i = 1;
	heu = 0;
	while (i < data->area)
	{
		if (data->goal_coor[i] != state[i])
			heu++;
		i++;
	}
	return (heu);
}

unsigned int	manhattan_dist(unsigned int *state, t_puzzle_data *data)
{
	unsigned int i;
	unsigned int heu;

	i = 1;
	heu = 0;
	while (i < data->area)
	{
		heu += distance(state[i], data->goal_coor[i], data->size);
		i++;
	}
	return (heu);
}

unsigned int	linear_conflict(unsigned int *state, t_puzzle_data *data)
{
	unsigned int i;
	unsigned int j;
	unsigned int line;
	unsigned int col;
	unsigned int heu;

	heu = data->heu[1](state, data);
	i = 1;
	while (i < data->area)
	{
		j = 1;
		line = state[i] / SIZE;
		col = state[i] % SIZE;
		while (j < data->area)
		{
			if (i != j)
			{
				if (line == (state[j] / SIZE) && line == (data->goal_coor[i]
							/ SIZE) && line == (data->goal_coor[j] / SIZE) &&
						state[i] > state[j] && data->goal_coor[i]
						< data->goal_coor[j])
					heu += 2;
				else if (col == (state[j] % SIZE) && col == (data->goal_coor[i]
							% SIZE) && col == (data->goal_coor[j] % SIZE) &&
						state[i] > state[j] && data->goal_coor[i] <
						data->goal_coor[j])
					heu += 2;
			}
			j++;
		}
		i++;
	}
	return (heu);
}

void			search_choice(t_puzzle_data *data)
{
	char	*line;
	int		choice;
	int		rep;

	ft_putendl("Type a number to choose a Search Algorithme:");
	ft_putendl("1: A*");
	ft_putendl("2: Greedy Search");
	ft_putendl("3: Uniform Cost");
	if ((rep = get_next_line(STDIN_FILENO, &line)) > 0 &&
			(choice = choice_verif(line)))
	{
		data->search_cost = 1;
		if (choice == 1)
			heuristic_choice(data);
		else if (choice == 2)
		{
			data->search_cost = 0;
			heuristic_choice(data);
		}
		else
			data->heu_choice = 0;
	}
	else
	{
		if (rep > 0)
			ft_memdel((void**)&line);
		search_choice(data);
	}
}

void			heuristic_choice(t_puzzle_data *data)
{
	char	*line;
	int		rep;

	ft_putendl("Type a number to choose a heuristic:");
	ft_putendl("1: Linear Conflict");
	ft_putendl("2: Manhattan Distance");
	ft_putendl("3: Hamming Distance");
	if ((rep = get_next_line(STDIN_FILENO, &line)) > 0 &&
			(HEU_CHOICE = choice_verif(line)))
	{
		ft_memdel((void**)&line);
	}
	else
	{
		if (rep > 0)
			ft_memdel((void**)&line);
		heuristic_choice(data);
	}
}

int				choice_verif(char *s)
{
	if (!is_num(s))
	{
		ft_putendl("Type a NUMBER to choose.");
		return (0);
	}
	if (ft_strlen(s) > 1)
	{
		ft_putendl("Only one number.");
		return (0);
	}
	if (ft_atoi(s) < 1 || ft_atoi(s) > 3)
	{
		ft_putendl("Number must be between 1 and 3.");
		return (0);
	}
	return (ft_atoi(s));
}
