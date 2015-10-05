/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2014/12/25 07:29:01 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <stdio.h>
# include <locale.h>
# define NUM_COLUMNS 8
# define SIX_M ((365 / 2) * 86400)
# define BUFF_SIZE 1024
# define S_IFWHT 0160000
# define S_ISWHT(m) (((m) & S_IFMT) == S_IFWHT)

typedef struct stat	t_stat;

typedef enum
{
	false,
	true
}	t_bool;

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	char			*filepath;
	char			*c0_prm;
	int				c1_nlink;
	char			*c2_uid;
	char			*c3_grp;
	long			c4_byt;
	char			*c5_ftm;
	char			*c6_fnm;
	quad_t			st_blocks;
	time_t			ctime;
	time_t			atime;
	time_t			btime;
	time_t			mtime;
	mode_t			st_mode;
	int				m_errno;
	char			*major;
}					t_btree;

size_t				g_numdirs;
size_t				g_numdirsprinted;

t_bool				g_lsl;
t_bool				g_lsr;
t_bool				g_lsbigr;
t_bool				g_lsa;
t_bool				g_lst;

t_bool				g_lsu;
t_bool				g_lsf;
t_bool				g_lsg;
t_bool				g_lsd;
t_bool				g_lsone;
t_bool				g_lsbigs;
t_bool				g_lsp;
t_bool				g_lsbigu;
t_bool				g_lsc;
t_bool				g_lsbiga;
t_bool				g_lsbigt;
t_bool				g_lsbigf;
t_bool				g_lso;

void				analyse_params(int numargs, char **argv);

int					analysedir_l(char *thedir);
int					analysedir(char *thedir);

char				*file_time(
struct stat *filestat, t_btree **node);

int					(*g_cmp)(t_btree **, t_btree **);

int					cmp_alpha(t_btree **root, t_btree **node);
int					cmp_mtime(t_btree **root, t_btree **node);
int					cmp_atime(t_btree **root, t_btree **node);
int					cmp_nosort(t_btree **root, t_btree **node);
int					cmp_size(t_btree **root, t_btree **node);
int					cmp_ctime(t_btree **root, t_btree **node);
int					cmp_btime(t_btree **root, t_btree **node);

int					processflags(char *flags);
int					error_illegalopt(char option);
int					error_print();
void				strerror_print(t_btree *node);

t_btree				*l_getfileinfo(char *file, int fulldir);
void				l_init_padding(size_t **padding);
char				*file_name(char *file_path);

void				cmp_setcomparator();

size_t				util_intlen(int number);
size_t				util_longlen(long number);
char				*util_checkdirslash(char *dir);
int					util_issymlinktargetdir(t_btree *thenode);
int					util_is_hidden(char *name);

void				btree_updatepadding(t_btree *node,
size_t padding[NUM_COLUMNS]);
void				padstr(char *str, size_t pad, int isl);
void				padnbr(int nbr, size_t pad);

quad_t				btree_insert_node(t_btree **root, t_btree **node);
t_btree				*btree_create_node();
void				btree_free_node(t_btree **node);
void				btree_print(t_btree *node, size_t padding[NUM_COLUMNS]);
void				btree_analysedir(t_btree *node);
void				btree_analyseerr(t_btree *node);
void				btree_printrow(t_btree	*node,
size_t padding[NUM_COLUMNS]);
void				btree_print_recursive(t_btree *node);
void				btree_updatepadding(t_btree *node,
size_t padding[NUM_COLUMNS]);

void				print_directoryname(t_btree *node, int override, int first);
void				print_totalbytes(int numfiles, int bytes);

void				update_fil_params(t_btree **root_fil, t_btree **node,
size_t padding[NUM_COLUMNS]);

void				checkbigf_p(t_btree *node);
#endif
