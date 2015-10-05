/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/11 18:13:51 by byoung-w          #+#    #+#             */
/*   Updated: 2014/12/25 01:15:16 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			btree_updatepadding(t_btree *node, size_t padding[NUM_COLUMNS])
{
	if ((g_lsa) ||
(!g_lsa && !util_is_hidden((file_name(node->filepath)))))
	{
		if (padding[1] < util_intlen(node->c1_nlink))
			padding[1] = util_intlen(node->c1_nlink);
		if (node->c2_uid != NULL)
			if ((int)padding[2] < (int)ft_strlen(node->c2_uid))
				padding[2] = ft_strlen(node->c2_uid);
		if (padding[3] < ft_strlen(node->c3_grp))
			padding[3] = ft_strlen(node->c3_grp);
		if (padding[4] < util_longlen(node->c4_byt))
			padding[4] = util_longlen(node->c4_byt);
		if (padding[5] < ft_strlen(node->c5_ftm))
			padding[5] = ft_strlen(node->c5_ftm);
		if (node->major != NULL)
			if ((int)padding[6] < (int)ft_strlen(node->major))
				padding[6] = ft_strlen(node->major);
	}
}

void			padstr(char *str, size_t pad, int isl)
{
	size_t		i;

	if (!isl)
		ft_putstr(str);
	if (((int)pad > (int)ft_strlen(str)))
	{
		i = pad - ft_strlen(str);
		while (i > 0)
		{
			ft_putchar(' ');
			i--;
		}
	}
	if (isl)
		ft_putstr(str);
}

void			padnbr(int nbr, size_t pad)
{
	size_t		i;

	if (((int)pad > (int)util_intlen(nbr)))
	{
		i = pad - util_intlen(nbr);
		while (i > 0)
		{
			ft_putchar(' ');
			i--;
		}
	}
	ft_putnbr(nbr);
}

void			l_init_padding(size_t **padding)
{
	int		i;

	i = 0;
	while (i < NUM_COLUMNS)
	{
		(*padding)[i] = 0;
		i++;
	}
}

quad_t			btree_insert_node(t_btree **root, t_btree **node)
{
	if (*root != NULL)
	{
		if (g_cmp(root, node))
		{
			if ((*root)->left == NULL)
				(*root)->left = *node;
			else
				btree_insert_node(&(*root)->left, node);
		}
		else
		{
			if ((*root)->right == NULL)
				(*root)->right = *node;
			else
				btree_insert_node(&(*root)->right, node);
		}
	}
	else
		*root = *node;
	if (!g_lsa && ((*node)->c6_fnm[0] == '.'))
		return (0);
	return ((*node)->st_blocks);
}
