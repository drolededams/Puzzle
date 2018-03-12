/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:03:06 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/12 16:42:06 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

t_state		*search_node_n(t_state *root, uint64_t id, unsigned int *coor, unsigned int area)
{
	if (root)
	{
		if (root->id == id && same_state(root->coor, coor, area))
			return (root); // a modifier pour puzzle > 4
		if (root->id > id)
			return(search_node_n(root->left, id, coor, area));
		else
			return(search_node_n(root->right, id, coor, area));
	}
	return (NULL);
}

t_state		**mem_hash_table_n(void)
{
	t_state **hash;

	if (!(hash = (t_state**)calloc(16777216, sizeof(t_state*))))
		exit_alloc_failed();
	return (hash);
}// a free

int		same_state(unsigned int *pre, unsigned int *suc, unsigned int area)
{
	unsigned int i;

	i = 0;
	while (i < area)
	{
		if (pre[i] != suc[i])
			return (0);
		i++;
	}
	return (1);
}
