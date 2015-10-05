/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/03 09:50:50 by byoung-w          #+#    #+#             */
/*   Updated: 2014/09/03 11:22:41 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

size_t		util_intlen(int number)
{
	int digits;

	digits = 0;
	if (number == 0)
		return (1);
	if (number < 0)
		digits = 1;
	while (number)
	{
		number /= 10;
		digits++;
	}
	return (digits);
}

size_t		util_longlen(long number)
{
	int digits;

	digits = 0;
	if (number < 0)
		digits = 1;
	while (number)
	{
		number /= 10;
		digits++;
	}
	return (digits);
}

char		*util_checkdirslash(char *dir)
{
	if (dir == NULL)
		return (dir);
	if (dir[ft_strlen(dir) - 1] != '/')
		return (ft_strjoin(dir, "/"));
	return (dir);
}

int			util_issymlinktargetdir(t_btree *thenode)
{
	char		buffer[9999];
	t_btree		*node;
	ssize_t		len;

	if (S_ISLNK(thenode->st_mode))
	{
		len = readlink(thenode->filepath, buffer, sizeof(buffer) - 1);
		if (len != -1)
		{
			buffer[len] = '\0';
			if ((node = l_getfileinfo(buffer, 1)))
				if (S_ISDIR(node->st_mode))
				{
					free(node);
					return (1);
				}
		}
	}
	return (0);
}

int			util_is_hidden(char *name)
{
	if (ft_strcmp(name, ".") == 0 && !g_lsbiga)
		return (1);
	if (ft_strcmp(name, "..") == 0 && !g_lsbiga)
		return (1);
	if (g_lsbiga)
	{
		if ((ft_strcmp(name, ".") == 0) || (ft_strcmp(name, "..") == 0))
			return (1);
		if (name[0] == '.')
			return (0);
	}
	return ((name[0] == '.') && (name[1] != '/'));
}
