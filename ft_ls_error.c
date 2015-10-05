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

static void		ft_putchar_err(char c)
{
	write(2, &c, 1);
}

static void		ft_putstr_err(char const *str)
{
	while (*str)
		write(2, str++, 1);
}

int				error_illegalopt(char option)
{
	ft_putstr_err("ls: illegal option -- ");
	ft_putchar_err(option);
	ft_putstr_err("\nusage: ls ");
	ft_putstr_err("[-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
	return (0);
}

int				error_print(void)
{
	perror("ls");
	return (0);
}

void			strerror_print(t_btree *node)
{
	char *err;

	err = strerror(node->m_errno);
	ft_putstr_err("ls: ");
	ft_putstr_err(node->c6_fnm);
	ft_putstr_err(": ");
	ft_putstr_err(err);
	ft_putchar_err('\n');
}
