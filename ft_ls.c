/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/03 09:50:50 by byoung-w          #+#    #+#             */
/*   Updated: 2014/12/25 07:37:20 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ls_args(char **argv, int numargs)
{
	if ((ft_strcmp(*argv, "-") == 0) && analysedir(*argv))
	{
		if (--numargs == 0)
			return (1);
		argv++;
	}
	else if (argv[0][0] == '-')
	{
		if (!processflags(argv[0]))
			return (0);
		numargs--;
		argv++;
		if ((numargs > 0) && (ft_strcmp(*argv, "--") == 0))
		{
			argv++;
			numargs--;
		}
	}
	cmp_setcomparator();
	if (numargs <= 0)
		return (analysedir("."));
	analyse_params(numargs, argv);
	return (0);
}

int				main(int argc, char **argv)
{
	g_cmp = &cmp_alpha;
	if (argc > 1)
	{
		argv++;
		return (ls_args(argv, argc - 1));
	}
	analysedir(".");
	return (0);
}
