/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/11 18:13:51 by byoung-w          #+#    #+#             */
/*   Updated: 2014/12/25 01:51:34 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_btree			*btree_create_node(void)
{
	t_btree		*newtree;

	newtree = (t_btree *)malloc(sizeof(t_btree));
	if (newtree == NULL)
		return (NULL);
	newtree->left = 0;
	newtree->right = 0;
	newtree->c0_prm = NULL;
	newtree->c2_uid = NULL;
	newtree->c3_grp = NULL;
	newtree->c5_ftm = NULL;
	newtree->c6_fnm = NULL;
	newtree->major = NULL;
	newtree->m_errno = 0;
	return (newtree);
}

void			btree_free_node(t_btree **node)
{
	if ((*node) == NULL)
		return ;
	if ((*node)->c0_prm != NULL)
		free((*node)->c0_prm);
	if ((*node)->c2_uid != NULL)
		free((*node)->c2_uid);
	if ((*node)->c3_grp != NULL)
		free((*node)->c3_grp);
	if ((*node)->c5_ftm != NULL)
		free((*node)->c5_ftm);
	if ((*node)->c6_fnm != NULL)
		free((*node)->c6_fnm);
	free((*node));
}

static void		btree_printsymlink(char *filepath)
{
	char	buffer[9999];
	ssize_t len;

	len = readlink(filepath, buffer, sizeof(buffer) - 1);
	if (len != -1)
	{
		buffer[len] = '\0';
		ft_putstr(" -> ");
		ft_putstr(buffer);
	}
}

void			checkbigf_p(t_btree *node)
{
	struct stat		sb;

	if ((g_lsp || g_lsbigf) && S_ISDIR(node->st_mode))
		ft_putchar('/');
	else if (g_lsbigf && !g_lsp)
	{
		if (S_ISLNK(node->st_mode) && g_lsbigf)
			ft_putchar('@');
		else if ((stat(node->filepath, &sb) == 0) && S_ISREG(sb.st_mode) &&
(sb.st_mode & 0111))
			ft_putchar('*');
		else if (S_ISSOCK(node->st_mode))
			ft_putchar('=');
		else if (S_ISWHT(node->st_mode))
			ft_putchar('%');
		else if (S_ISFIFO(node->st_mode))
			ft_putchar('|');
	}
	if (S_ISLNK(node->st_mode) && g_lsl)
		btree_printsymlink(node->filepath);
	ft_putchar('\n');
}
