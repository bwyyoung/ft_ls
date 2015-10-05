/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_t.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/03 09:50:50 by byoung-w          #+#    #+#             */
/*   Updated: 2014/09/03 11:22:41 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static char		*file_time_bigt(char *time)
{
	char	*time1;

	time1 = ft_strsub(time, 4, ft_strlen(time) - 5);
	return (time1);
}

static char		*file_time_yyyy(char *time)
{
	char	*time1;
	char	*year;

	year = ft_strsub(time, ft_strlen(time) - 5, 4);
	time1 = ft_strsub(time, 4, ft_strlen(time) - 4);
	time = ft_strsub(time1, 0, 7);
	free(time1);
	time1 = ft_strjoin(time, " ");
	free(time);
	time = ft_strjoin(time1, year);
	free(time1);
	free(year);
	return (time);
}

static char		*file_time_6m(char *time)
{
	char	*time1;
	int		i;
	int		j;

	j = 0;
	time = ft_strsub(time, 4, ft_strlen(time) - 5);
	i = ft_strlen(time);
	while (time[i + 1] != ':')
		i--;
	time1 = ft_memalloc(i + 1);
	while (j <= i)
	{
		time1[j] = time[j];
		j++;
	}
	time1[j] = '\0';
	return (time1);
}

static char		*file_time_mode(struct stat *filestat, t_btree **node,
char *mtime, time_t mtime2)
{
	time_t	current_time;

	current_time = time(NULL);
	if (g_lsbigu && g_lsl)
	{
		mtime = ctime(&filestat->st_birthtime);
		mtime2 = (*node)->btime;
	}
	if (g_lsu && g_lsl)
	{
		mtime = ctime(&filestat->st_atime);
		mtime2 = (*node)->atime;
	}
	if (g_lsc && g_lsl)
	{
		mtime = ctime(&filestat->st_ctime);
		mtime2 = (*node)->ctime;
	}
	if (g_lsbigt)
		return (file_time_bigt(mtime));
	else if ((current_time - SIX_M <= mtime2) &&
(mtime2 <= current_time))
		return (file_time_6m(mtime));
	else
		return (file_time_yyyy(mtime));
}

char			*file_time(struct stat *filestat, t_btree **node)
{
	char	*mtime;
	time_t	mtime2;

	(*node)->btime = filestat->st_birthtime;
	(*node)->ctime = filestat->st_ctime;
	(*node)->atime = filestat->st_atime;
	(*node)->mtime = filestat->st_mtime;
	mtime = ctime(&filestat->st_mtime);
	mtime2 = (*node)->mtime;
	return (file_time_mode(filestat, node, mtime, mtime2));
}
