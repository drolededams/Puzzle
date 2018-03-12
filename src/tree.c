/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:03:06 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/09 16:48:58 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N-Puzzle.h"

void		add_node(t_state **root, t_state *state)
{
	if (*root == NULL)
		*root = state;
	else if ((*root)->id > ID)
		add_node(&(*root)->left, state);
	else
		add_node(&(*root)->right, state);
}

t_state		*search_node(t_state *root, uint64_t id)
{
	if (root)
	{
		if (root->id == id)
			return (root); // a modifier pour puzzle > 4
		if (root->id > id)
			return(search_node(root->left, id));
		else
			return(search_node(root->right, id));
	}
	return (NULL);
}

t_state		**mem_hash_table(void)
{
	t_state **hash;

	if (!(hash = (t_state**)calloc(sizeof(t_state*), 1024)))
		exit_alloc_failed();
	return (hash);
}// a free

