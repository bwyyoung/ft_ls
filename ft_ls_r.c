/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/03 09:50:50 by byoung-w          #+#    #+#             */
/*   Updated: 2014/12/25 07:49:13 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void				print_directoryname(t_btree *node, int override, int first)
{
	if ((g_lsa) || (!g_lsa &&
!util_is_hidden((file_name(node->filepath)))) || override)
		if (g_numdirs > 1)
		{
			if (!first)
				ft_putchar('\n');
			ft_putstr(node->filepath);
			ft_putstr(":\n");
		}
}

void				print_totalbytes(int numfiles, int bytes)
{
	if (numfiles > 0 && g_lsl)
	{
		ft_putstr("total ");
		ft_putnbr(bytes);
		ft_putchar('\n');
	}
}

void				btree_print_recursive(t_btree *node)
{
	if (!g_lsbigr)
		return ;
	if ((node) == NULL)
		return ;
	if (g_lsr)
		btree_print_recursive((node)->right);
	else
		btree_print_recursive((node)->left);
	if ((ft_strcmp(node->c6_fnm, ".") && ft_strcmp(node->c6_fnm, "..")) &&
!(S_ISLNK(node->st_mode)) && (S_ISDIR(node->st_mode)))
	{
		if (((g_lsa) ||
(!g_lsa && ((file_name(node->filepath)[0]) != '.'))))
		{
			g_numdirs++;
			print_directoryname(node, 0, 0);
			analysedir(node->filepath);
		}
	}
	if (g_lsr)
		btree_print_recursive((node)->left);
	else
		btree_print_recursive((node)->right);
	btree_free_node(&node);
}
