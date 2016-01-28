/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 11:41:51 by fviolin           #+#    #+#             */
/*   Updated: 2016/01/28 18:21:19 by fviolin          ###   ########.fr       */
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

typedef struct				s_lst_info
{
	struct t_data			*file_data;
	struct s_lst_info		*next;
}							t_lst_info;

typedef struct				s_data
{
	char					*get_rights; //permissions
	char					*link; // nlink_t nb de fichiers/sous dossiers/fichiers
	char					*uid; // owner name
	char					*gid; // group name
	char					*size; // off_t taille en octets du fichier/dossier
	char					*date; // month + day + time
	char					*name; // file/rep name
}							t_data;

t_lst_info	*ft_create_lst(struct dirent *ret, struct stat *file_stat);
void		ft_new_node(t_lst_info **head, t_lst_info *new_node);
void		ft_add_data(t_lst_info *new_node, struct stat *file_stat);
void		ft_free_lst(t_lst_info **head);

void		ft_get_rights(t_lst_info *get_stat, struct stat *file_stat);
t_lst_info	*ft_stat(struct dirent *ret, struct stat *file_stat);

#endif
