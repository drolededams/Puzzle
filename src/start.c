/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:30:22 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/02 21:37:28 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void	pre_start_a(t_puzzle_data *data)
{
	t_state	*start;
	t_heap	*heap;
	t_state **hash_tab;
	unsigned int size;
	uint64_t id_goal;
	uint64_t (*move[4])(t_state *state, unsigned int size);

	hash_tab = mem_hash_table();
	size = data->size * data->size;
	start = mem_state_4(id_state(data->state_coor, size), NULL, size, data->goal_coor);
	start->cost = 0;
	printf("%" PRIu64 "\n", start->id);
	id_goal = id_state(data->goal_coor, size);
	printf("%" PRIu64 "\n", id_goal);
	heap = mem_heap();
	push_heap(heap, start);
	add_node(&hash_tab[hash_table(start->id)], start);
	move[0] = up_tile;
	move[1] = down_tile;
	move[2] = left_tile;
	move[3] = right_tile;
	start_a(heap, id_goal, hash_tab, size, move, data->goal_coor);
	//lib mem data
}

void	start_a(t_heap *heap, uint64_t id_goal, t_state **hash_tab, unsigned int size, uint64_t (*move[4])(t_state *, unsigned int), unsigned int *goal_coor)
{
	int success;
	int i;
	int count;
	int count_2;
	uint64_t id_successor;
	t_state *state;
	t_state *successor;
	success = 0;
	count = 0;
	count_2 = 1;
	while (H_SIZE > 0 && !success)
	{
		count++;
		state = pop_heap(heap); 
		if (state->id == id_goal)
			success = 1;
		else
		{
			i = -1;
			while(++i < 4)
			{
				if ((id_successor = move[i](state, ft_sqrt(size))))
				{
					if (!(successor = search_node(hash_tab[hash_table(id_successor)], id_successor)))
					{
						count_2++;
						successor = mem_state_4(id_successor, state, size, goal_coor);
						successor->cost = state->cost + 1;
						push_heap(heap, successor);
						add_node(&hash_tab[hash_table(successor->id)], successor);
					}
					else if (successor->cost > state->cost + 1)
					{
						successor->pre = state;
						successor->cost = state->cost + 1;
						if(!successor->i_heap)
							push_heap(heap, successor);
						else
							up_heap(heap, successor->i_heap);
					}
				}
			}
		}
	}
	int tour;
	tour = 0;
	ft_putendl("Display result");
	while(state != NULL)
	{
		tour++;
		print_coor(state->value, size);
		printf("%" PRIu64 "\n", state->id);
		printf("heuristique = %u \n", state->heu);
		printf("cout = %u \n", state->cost);
		printf("hash = %u \n", hash_table(state->id));
		ft_putendl("pre");
		state = state->pre;
	}
	printf("etape = %d \n", tour);
	printf("cout memoire = %d \n", count_2);
	ft_putnbr(count);
	ft_putchar('\n');
	ft_putnbr(H_SIZE);
	ft_putchar('\n');
}
