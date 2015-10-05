/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/11 18:13:51 by byoung-w          #+#    #+#             */
/*   Updated: 2014/12/25 07:37:46 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			btree_printrow_l_gchecks(t_btree *node,
size_t padding[NUM_COLUMNS])
{
	ft_putstr(node->c0_prm);
	ft_putchar(' ');
	padnbr(node->c1_nlink, padding[1]);
	ft_putchar(' ');
	if (!g_lsg && (node->c2_uid != NULL))
	{
		padstr(node->c2_uid, padding[2], 0);
		ft_putstr("  ");
	}
	if (!g_lso)
	{
		padstr(node->c3_grp, padding[3], 0);
		ft_putstr("  ");
	}
	if (g_lsg && g_lso)
		ft_putstr("  ");
}

static void			btree_printrow_l(t_btree *node,
size_t padding[NUM_COLUMNS])
{
	btree_printrow_l_gchecks(node, padding);
	if (node->major != NULL)
	{
		padstr(node->major, padding[6], 1);
		ft_putstr(" ");
	}
	else if (padding[6] > 0)
		padstr("", padding[6] + 1, 1);
	padnbr(node->c4_byt, padding[4]);
	ft_putchar(' ');
	padstr(node->c5_ftm, padding[5], 0);
	ft_putchar(' ');
	ft_putstr(node->c6_fnm);
	checkbigf_p(node);
}

static void			btree_printname(t_btree *node)
{
	ft_putstr(node->c6_fnm);
	checkbigf_p(node);
}

void				btree_print(t_btree *node,
size_t padding[NUM_COLUMNS])
{
	if ((node) == NULL)
		return ;
	if (g_lsr)
		btree_print((node)->right, padding);
	else
		btree_print((node)->left, padding);
	if ((g_lsa) ||
(!g_lsa && !util_is_hidden(node->c6_fnm)))
	{
		if (g_lsl)
			btree_printrow_l(node, padding);
		else
			btree_printname(node);
	}
	if (g_lsr)
		btree_print((node)->left, padding);
	else
		btree_print((node)->right, padding);
	if (!g_lsbigr)
		btree_free_node(&node);
}
