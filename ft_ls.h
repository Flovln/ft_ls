/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 11:41:51 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/01 16:47:16 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <pwd.h>
#include <uuid/uuid.h>
#include <dirent.h> // opendir readdir closedir
#include <sys/stat.h>
#include <sys/types.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
/*
typedef struct 		s_opt
{
	int				l;
	int				R;
	int				a;
	int				r;
	int				t;
}					t_opt;
*/
typedef struct				s_lst
{
	char					*size;
	char					*links;
	char					get_perm[11];
	char					*date;
	char					*name;
	char					*uid;
	char					*gid;
	//t_data					*file_data;
	struct s_lst			*next;
}							t_lst;
/*
typedef struct				s_data
{
	char				*date;
   char					*links; // nlink_t nb de fichiers/sous dossiers/fichiers
   char					*uid; // owner name
   char					*gid; // group name
   char					*size; // off_t taille en octets du fichier/dossier
}							t_data;
*/
void		ft_perm_acc(t_lst *elem, struct stat *file_stat);
void		ft_add_node(t_lst *head, t_lst *new_node);
t_lst		*ft_get_data(t_lst *head, char *path, char *file);

#endif
