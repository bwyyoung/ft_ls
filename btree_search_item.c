/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/11 18:13:51 by byoung-w          #+#    #+#             */
/*   Updated: 2014/09/11 18:14:24 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				*btree_search_filepath(t_btree *root, void *data_ref,
int (*cmpf)(void *, void *))
{
	if (root != NULL)
	{
		btree_search_filepath(root->left, data_ref, cmpf);
		if (cmpf(root->filepath, data_ref) == 0)
			return (data_ref);
		btree_search_filepath(root->right, data_ref, cmpf);
	}
	return (NULL);
}

void				btree_analysedir(t_btree *node)
{
	if ((node) == NULL)
		return ;
	if (g_lsr)
		btree_analysedir((node)->right);
	else
		btree_analysedir((node)->left);
	print_directoryname(node, 1, (g_numdirsprinted == 0));
	g_numdirsprinted++;
	analysedir(node->filepath);
	if (g_lsr)
		btree_analysedir((node)->left);
	else
		btree_analysedir((node)->right);
	btree_free_node(&node);
}

void				btree_analyseerr(t_btree *node)
{
	if ((node) == NULL)
		return ;
	btree_analyseerr((node)->left);
	strerror_print(node);
	btree_analyseerr((node)->right);
	btree_free_node(&node);
}
