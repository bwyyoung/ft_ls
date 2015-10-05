/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/03 09:50:50 by byoung-w          #+#    #+#             */
/*   Updated: 2014/12/25 06:56:39 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static int		getacl(char *name)
{
	acl_t		facl;
	acl_entry_t	ae;

	facl = acl_get_link_np(name, ACL_TYPE_EXTENDED);
	if (facl && (acl_get_entry(facl, ACL_FIRST_ENTRY, &ae) == -1))
	{
		acl_free(facl);
		return (0);
	}
	if (facl != NULL)
	{
		acl_free(facl);
		return (1);
	}
	acl_free(facl);
	return (0);
}

static char		filetype(struct stat fstat, mode_t st_mode, t_btree **node)
{
	char	*c;

	if (S_ISCHR(st_mode) || S_ISBLK(st_mode))
	{
		c = ft_itoa(major(fstat.st_rdev));
		(*node)->c4_byt = minor(fstat.st_rdev);
		(*node)->major = ft_strjoin(c, ",");
		free(c);
		if (S_ISBLK(st_mode))
			return ('b');
		return ('c');
	}
	if (S_ISDIR(st_mode))
		return ('d');
	if (S_ISLNK(st_mode))
		return ('l');
	if (S_ISSOCK(st_mode))
		return ('s');
	if (S_ISFIFO(st_mode))
		return ('p');
	return ('-');
}

static void		getfp_rwx(struct stat fstat, t_btree **node)
{
	(*node)->st_mode = fstat.st_mode;
	(*node)->c0_prm[0] = filetype(fstat, fstat.st_mode, node);
	(*node)->c0_prm[1] = (fstat.st_mode & S_IRUSR) ? 'r' : '-';
	(*node)->c0_prm[2] = (fstat.st_mode & S_IWUSR) ? 'w' : '-';
	(*node)->c0_prm[3] = (fstat.st_mode & S_IXUSR) ? 'x' : '-';
	(*node)->c0_prm[3] = ((fstat.st_mode & S_IXUSR) &&
(S_ISUID & fstat.st_mode)) ? 's' : (*node)->c0_prm[3];
	(*node)->c0_prm[3] = (!(fstat.st_mode & S_IXUSR) &&
(S_ISUID & fstat.st_mode)) ? 'S' : (*node)->c0_prm[3];
	(*node)->c0_prm[4] = (fstat.st_mode & S_IRGRP) ? 'r' : '-';
	(*node)->c0_prm[5] = (fstat.st_mode & S_IWGRP) ? 'w' : '-';
	(*node)->c0_prm[6] = (fstat.st_mode & S_IXGRP) ? 'x' : '-';
	(*node)->c0_prm[6] = ((fstat.st_mode & S_IXGRP) &&
(S_ISGID & fstat.st_mode)) ? 's' : (*node)->c0_prm[6];
	(*node)->c0_prm[6] = (!(fstat.st_mode & S_IXGRP) &&
(S_ISGID & fstat.st_mode)) ? 'S' : (*node)->c0_prm[6];
	(*node)->c0_prm[7] = (fstat.st_mode & S_IROTH) ? 'r' : '-';
	(*node)->c0_prm[8] = (fstat.st_mode & S_IWOTH) ? 'w' : '-';
	(*node)->c0_prm[9] = (fstat.st_mode & S_IXOTH) ? 'x' : '-';
}

static char		*getfp(struct stat fstat, char *file_path, t_btree **node)
{
	char			sticky;
	struct passwd	*pwd;

	sticky = 't';
	if (!((*node)->c0_prm = ft_memalloc(12)))
		return (NULL);
	getfp_rwx(fstat, node);
	if ((*node)->c0_prm[9] == '-')
		sticky = 'T';
	(*node)->c0_prm[9] = (fstat.st_mode & S_ISVTX) ?
sticky : (*node)->c0_prm[9];
	(*node)->c0_prm[10] = ' ';
	if (listxattr(file_path, NULL, 100000, ((*node)->c0_prm[0] == 'l' ?
XATTR_NOFOLLOW : 0)) > 0)
		(*node)->c0_prm[10] = '@';
	else if (getacl(file_path))
		(*node)->c0_prm[10] = '+';
	(*node)->c0_prm[11] = '\0';
	(*node)->c1_nlink = fstat.st_nlink;
	if ((pwd = getpwuid(fstat.st_uid)) != NULL)
		(*node)->c2_uid = ft_strdup(pwd->pw_name);
	else
		(*node)->c2_uid = ft_itoa(fstat.st_uid);
	return ((*node)->c0_prm);
}

t_btree			*l_getfileinfo(char *file, int fulldir)
{
	struct group	*grp;
	struct stat		filestat;
	t_btree			*node;

	if (!(node = btree_create_node()))
		return (NULL);
	if (!fulldir)
		node->c6_fnm = file_name(file);
	else
		node->c6_fnm = ft_strdup(file);
	if (lstat(file, &filestat) != 0 && (node->m_errno = errno))
		return (node);
	node->c4_byt = filestat.st_size;
	getfp(filestat, file, &node);
	grp = getgrgid(filestat.st_gid);
	if (grp != NULL)
		node->c3_grp = ft_strdup(grp->gr_name);
	else
		node->c3_grp = ft_itoa(filestat.st_gid);
	node->filepath = file;
	node->c5_ftm = file_time(&filestat, &node);
	node->st_blocks = filestat.st_blocks;
	return (node);
}
