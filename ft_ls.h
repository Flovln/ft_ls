/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 11:41:51 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/02 17:35:51 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <pwd.h>
# include <uuid/uuid.h>
# include <dirent.h> // opendir readdir closedir
# include <sys/stat.h>
# include <sys/types.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

/*
typedef struct 				s_opt
{
	int						l;
	int						R;
	int						a;
	int						r;
	int						t;
}							t_opt;
*/

typedef struct				s_pad
{
	size_t					links;
	size_t					uid;
	size_t					gid;
	size_t					size;
}							t_pad;

typedef struct				s_data
{
	char					get_perm[11];
	char					*links;
	char					*uid;
	char					*gid;
	char					*size;
}							t_data;

typedef struct				s_lst
{
//	char					*path;
	t_data					*file_data;
	char					*date;
	char					*name;
	struct s_lst			*next;
}							t_lst;

void						ft_perm_acc(t_lst *elem, struct stat *file_stat);
void						ft_add_node(t_lst *head, t_lst *new_node);
t_lst						*ft_get_data(t_lst *head, char *path, char *file);
void						ft_padding(t_lst *head, t_pad *pad);
//void						ft_sort_lst(t_lst *head);

#endif
