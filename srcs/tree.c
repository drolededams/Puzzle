/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:03:06 by dgameiro          #+#    #+#             */
/*   Updated: 2018/09/28 15:01:00 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/npuzzle.h"

void			add_node(t_state **root, t_state *state)
{
	if (*root == NULL)
		*root = state;
	else if ((*root)->id > state->id)
		add_node(&(*root)->left, state);
	else
		add_node(&(*root)->right, state);
}

t_state			*search_node(t_state *root, uint64_t id)
{
	if (root)
	{
		if (root->id == id)
			return (root);
		if (root->id > id)
			return (search_node(root->left, id));
		else
			return (search_node(root->right, id));
	}
	return (NULL);
}

unsigned int	hash_table(uint64_t id, unsigned int area)
{
	unsigned int x;
	unsigned int i;
	unsigned int hash;

	x = 1;
	i = 0;
	hash = 0;
	while (x != 0)
		x = (id >> 4 * i++) & 0xF;
	if (i == 1)
	{
		hash = (id >> 4) & 0xF;
		hash = hash << 8;
	}
	else if (i == area)
		hash = ((i - 1) << 4) | ((id >> 4 * (i - 2)) & 0xF);
	else
	{
		hash = (id >> (4 * i)) & 0xF;
		hash = (hash << 4) | i;
		hash = (hash << 4) | (id >> 4 * (i - 2) & 0xF);
	}
	return (hash & 1023);
}

t_state			**mem_hash_table(void)
{
	t_state **hash;

	if (!(hash = (t_state**)calloc(1024, sizeof(t_state*))))
		exit_alloc_failed();
	return (hash);
}

void			free_tree(t_state *node)
{
	if (node == NULL)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	if (node->value)
		free(node->value);
	if (node->coor)
		free(node->coor);
	free(node);
}
