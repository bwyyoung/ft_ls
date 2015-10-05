/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_cmp2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/03 09:50:50 by byoung-w          #+#    #+#             */
/*   Updated: 2014/09/03 11:22:41 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmp_ctime(t_btree **root, t_btree **node)
{
	if ((*root)->ctime < (*node)->ctime)
		return (1);
	else if ((*root)->ctime == (*node)->ctime)
		return (cmp_alpha(root, node));
	return (0);
}

int		cmp_btime(t_btree **root, t_btree **node)
{
	if ((*root)->btime < (*node)->btime)
		return (1);
	else if ((*root)->btime == (*node)->btime)
		return (cmp_alpha(root, node));
	return (0);
}
