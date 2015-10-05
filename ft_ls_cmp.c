/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_cmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/03 09:50:50 by byoung-w          #+#    #+#             */
/*   Updated: 2014/09/03 11:22:41 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmp_nosort(t_btree **root, t_btree **node)
{
	(void)root;
	(void)node;
	return (0);
}

int		cmp_alpha(t_btree **root, t_btree **node)
{
	if ((ft_strcmp((*root)->c6_fnm, (*node)->c6_fnm) > 0))
		return (1);
	return (0);
}

int		cmp_mtime(t_btree **root, t_btree **node)
{
	if ((*root)->mtime < (*node)->mtime)
		return (1);
	else if ((*root)->mtime == (*node)->mtime)
		return (cmp_alpha(root, node));
	return (0);
}

int		cmp_atime(t_btree **root, t_btree **node)
{
	if (g_lsl && !g_lst)
		return (cmp_alpha(root, node));
	if ((*root)->atime < (*node)->atime)
		return (1);
	return (0);
}

int		cmp_size(t_btree **root, t_btree **node)
{
	if ((*root)->c4_byt < (*node)->c4_byt)
		return (1);
	if ((*root)->c4_byt == (*node)->c4_byt)
		return (cmp_alpha(root, node));
	return (0);
}
