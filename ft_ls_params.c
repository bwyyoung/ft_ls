/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/03 09:50:50 by byoung-w          #+#    #+#             */
/*   Updated: 2014/09/03 11:22:41 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static void		print_params(t_btree *root_dir, t_btree *root_fil,
size_t padding[NUM_COLUMNS])
{
	int		lsa;

	lsa = g_lsa;
	if (g_lsd)
		g_lsa = 1;
	btree_print(root_fil, padding);
	if (g_lsd)
		g_lsa = 0;
	g_lsa = lsa;
	if (root_fil != NULL && root_dir != NULL)
		ft_putchar('\n');
	btree_analysedir(root_dir);
}

static int		break_params_node(t_btree **node, t_btree **root_dir
, t_btree **root_err)
{
	if ((*node)->m_errno > 0)
	{
		btree_insert_node(root_err, node);
		g_numdirs++;
		return (1);
	}
	else if ((S_ISDIR((*node)->st_mode) ||
(util_issymlinktargetdir((*node)))) && !g_lsd)
	{
		g_numdirs++;
		btree_insert_node(root_dir, node);
		return (1);
	}
	return (0);
}

static void		break_params(int (*m_cmp)(t_btree **, t_btree **),
size_t padding[NUM_COLUMNS], int numargs, char **argv)
{
	t_btree		*node;
	t_btree		*root_dir;
	t_btree		*root_fil;
	t_btree		*root_err;

	root_dir = NULL;
	root_fil = NULL;
	root_err = NULL;
	while (numargs > 0)
	{
		if (!(node = l_getfileinfo(*argv, 1)))
			return ;
		if (!break_params_node(&node, &root_dir, &root_err))
			update_fil_params(&root_fil, &node, padding);
		argv++;
		numargs--;
	}
	btree_analyseerr(root_err);
	g_cmp = m_cmp;
	print_params(root_dir, root_fil, padding);
}

void			analyse_params(int numargs, char **argv)
{
	int			(*m_cmp)(t_btree **, t_btree **);
	size_t		padding[NUM_COLUMNS];
	size_t		*p;

	m_cmp = g_cmp;
	g_cmp = &cmp_alpha;
	p = padding;
	l_init_padding(&p);
	break_params(m_cmp, padding, numargs, argv);
}
