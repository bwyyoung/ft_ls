/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/03 09:50:50 by byoung-w          #+#    #+#             */
/*   Updated: 2014/09/03 11:22:41 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static int		checkflag_bonus_2(char flag)
{
	if (flag == 'o')
	{
		g_lso = 1;
		g_lsone = 0;
	}
	else if (flag == 'F')
	{
		g_lsbigf = 1;
		g_lsp = 0;
	}
	else if (flag == 'U')
	{
		g_lsbigu = 1;
		g_lsc = 0;
	}
	else if (flag == 'u')
	{
		g_lsu = 1;
		g_lsc = 0;
	}
	else
		return (0);
	return (1);
}

int				checkflag_bonus_1(char flag)
{
	if (flag == 'g')
	{
		g_lsg = 1;
		g_lsone = 0;
	}
	else if (flag == 'd')
		g_lsd = 1;
	else if (flag == 'S')
		g_lsbigs = 1;
	else if (flag == 'p')
		g_lsp = 1;
	else if (flag == 'c')
	{
		g_lsc = 1;
		g_lsu = 0;
		g_lsbigu = 0;
	}
	else if (flag == 'T')
		g_lsbigt = 1;
	else
		return (checkflag_bonus_2(flag));
	return (1);
}

int				checkflag(char flag)
{
	if (flag == 'a')
		g_lsa = 1;
	else if (flag == 'l')
	{
		g_lsone = 0;
		g_lsl = 1;
	}
	else if (flag == 'r')
		g_lsr = 1;
	else if (flag == 'R')
		g_lsbigr = 1;
	else if (flag == 't')
		g_lst = 1;
	else if (flag == '1')
	{
		g_lsone = 1;
		g_lsl = 0;
	}
	else if (flag == 'A')
		g_lsbiga = 1;
	else if (flag == 'f')
		g_lsf = 1;
	else
		return (checkflag_bonus_1(flag));
	return (1);
}

int				processflags(char *flags)
{
	int		i;

	i = 1;
	while (flags[i] != '\0')
	{
		if (!checkflag(flags[i]))
			return (error_illegalopt(flags[i]));
		i++;
	}
	return (1);
}

void			cmp_setcomparator(void)
{
	g_cmp = &cmp_alpha;
	if (!g_lsl && !g_lst)
		g_lsu = false;
	if (g_lst)
		g_cmp = &cmp_mtime;
	if (g_lsu)
		g_cmp = &cmp_atime;
	if (g_lsbigs)
		g_cmp = &cmp_size;
	if (g_lsbigu && g_lst)
		g_cmp = &cmp_btime;
	if (g_lsc && g_lst)
		g_cmp = &cmp_ctime;
	if (g_lsf)
	{
		g_lst = false;
		g_lsa = true;
		g_cmp = &cmp_nosort;
	}
	if (g_lsg && !g_lsone)
		g_lsl = 1;
	if (g_lso && !g_lsone)
		g_lsl = 1;
}
