/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:29:23 by dgameiro          #+#    #+#             */
/*   Updated: 2018/02/23 18:15:43 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	verif_puzzle(t_puzzle_data *data)
{
	ft_putendl("Good numbers");
	good_numbers(data);
	ft_putendl("Is Soluble");
	is_soluble(data);
	ft_putendl("fin");
}

void	good_numbers(t_puzzle_data *data)
{
	int i;

	i = -1;
	while (++i < data->size * data->size)
		if (!(is_in_puzzle(data, i)))
			exit_bad_puzzle(data, NUMBER_MISSING);
}

int		is_in_puzzle(t_puzzle_data *data, int n)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < data->size)
	{
		while (++j < data->size)
			if (data->puzzle[i][j] == n)
				return (1);
		j = -1;
	}
	return (0);
}

void	exit_bad_puzzle(t_puzzle_data *data, int code)
{
	if (code == NUMBER_MISSING)
		ft_putendl("Number missing in the N-Puzzle.");
	else if (code == IMPOSSIBLE)
		ft_putendl("The N-Puzzle can't be solved.");
	ft_memdel((void**)&data);
	exit(0);
}

t_coor	where_is(t_puzzle_data *data, int value)
{
	t_coor coor;

	coor.x = -1;
	coor.y = -1;
	while(++coor.y < data->size)
	{
		while(++coor.x < data->size)
			if(data->puzzle[coor.y][coor.x] == value)
				return (coor);
		coor.x = -1;
	}
	return(coor);
}

void	is_soluble(t_puzzle_data *data)
{
	int i;
	int blank_dis;
	int permutation;
	
	i = -1;
	coor_alloc(data);
	func_init(data);
	while (++i < data->size * data->size)
	{
		data->state_coor[i] = where_is(data, i);//a l'envers fait o(n) et non o(n^2)
		data->goal_coor[i] = find_final_coor(data, i);
	}
	blank_dis = distance(data->state_coor[0], data->goal_coor[0]) % 2;
	permutation = permutation_calc(data) % 2;

	if (blank_dis == permutation)
		ft_putendl("Puzzle Soluble");
	else
		exit_bad_puzzle(data, IMPOSSIBLE);
}

void	coor_alloc(t_puzzle_data *data)
{
	
	if(!(data->state_coor = (t_coor*)malloc(sizeof(t_coor) * ft_power(data->size, 2))))
		exit_alloc_failed();
	if(!(data->goal_coor = (t_coor*)malloc(sizeof(t_coor) * ft_power(data->size, 2))))
		exit_alloc_failed();
}

t_coor	*coor_copy(t_coor *coor, int size)
{
	t_coor *copy;
	int i;

	if(!(copy = (t_coor*)malloc(sizeof(t_coor) * size)))
		exit_alloc_failed();
	i = -1;
	while(++i < size)
		copy[i] = coor[i];
	return (copy);
}

int		permutation_calc(t_puzzle_data *data)
{
	int i;
	int j;
	int size;
	int perm;
	t_coor *copy;

	i = 0;
	j = 1;
	perm = 0;
	copy = coor_copy(data->state_coor, data->size * data->size);//a voir copy
	size = data->size * data->size - 1;
	/*ft_putendl("copy");
	print_coor(copy, data);
	ft_putendl("state");
	print_coor(data->state_coor, data);*/
	while(i < size && j < size + 1)
	{
		if(copy[i].x != data->goal_coor[i].x ||
				copy[i].y != data->goal_coor[i].y)
		{	
			swap_coor(copy, i, j);
			j++;
			perm++;
		}
		else
		{
			i++;
			j = i + 1;
		}
	}
	/*ft_putendl("copy");
	print_coor(copy, data);
	ft_putendl("state");
	print_coor(data->state_coor, data);*/
	return (perm);
}

void	swap_coor(t_coor	*copy, int i, int j)
{
	t_coor tmp;

	tmp = copy[i];
	copy[i] = copy[j];
	copy[j] = tmp;
}

void print_coor(t_coor *coor, t_puzzle_data *data)
{
	int i;

	i = 0;
	while (i < data->size * data->size)
	{
	  ft_putnbr(coor[i].x);
	  ft_putchar(',');
	  ft_putnbr(coor[i].y);
	  ft_putchar('\n');
	  i++;
	}
}
