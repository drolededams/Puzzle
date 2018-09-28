/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristic_choice.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 14:44:57 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/28 14:46:11 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

static void			print_search_choice(void)
{
	ft_putendl("Type a number to choose a Search Algorithme:");
	ft_putendl("1: A*");
	ft_putendl("2: Greedy Search");
	ft_putendl("3: Uniform Cost");
}

void				search_choice(t_puzzle_data *data)
{
	char	*line;
	int		choice;
	int		rep;

	print_search_choice();
	if ((rep = get_next_line(STDIN_FILENO, &line)) > 0 &&
			(choice = choice_verif(line)))
	{
		data->search_cost = 1;
		if (choice == 1 || choice == 2)
		{
			if (choice == 2)
				data->search_cost = 0;
			heuristic_choice(data);
		}
		else
			data->heu_choice = 0;
		ft_memdel((void**)&line);
	}
	else
	{
		if (rep > 0)
			ft_memdel((void**)&line);
		search_choice(data);
	}
}

void				heuristic_choice(t_puzzle_data *data)
{
	char	*line;
	int		rep;

	ft_putendl("Type a number to choose a heuristic:");
	ft_putendl("1: Linear Conflict");
	ft_putendl("2: Manhattan Distance");
	ft_putendl("3: Hamming Distance");
	if ((rep = get_next_line(STDIN_FILENO, &line)) > 0 &&
			(data->heu_choice = choice_verif(line)))
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

int					choice_verif(char *s)
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
