/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 11:41:51 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/11 11:28:37 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <pwd.h>
# include <uuid/uuid.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct				s_opt
{
	int						l;
	int						R;
	int						a;
	int						r;
	int						t;
}							t_opt;

typedef struct				s_pad
{
	size_t					links;
	size_t					uid;
	size_t					gid;
	size_t					size;
}							t_pad;

typedef struct				s_data
{
	char					*blocks;
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
	char					*date; //time display
	int						last_edit; //time sort
	char					*name;
	struct s_lst			*next;
}							t_lst;

void						ft_add_data(struct stat file_stat,
								t_lst *node, char *file);
void						ft_add_node(t_lst **head, t_lst *current,
								t_lst *new_node);
t_lst						*ft_get_data(t_lst *head, char *path, char *file);
void						ft_padding(t_lst **head, t_pad *pad);
int							ft_check_opt(t_opt *opt);
int							ft_valid_opt(char c);
int							ft_options(char *s, t_opt *opt);
void						ft_init_opt(t_opt *opt);
void						ft_display_data(t_lst **node);
void						ft_display_total(t_lst **node);
void						ft_display_curr(t_lst **node, int i); // ls
void						ft_display_l(t_lst **node, int i); // ls -l && -a
void						ft_display_r(t_lst **node, int i); // ls -r && -a
void						ft_display_t(t_lst **node); // ls -t
void						ft_display_l_r(t_lst **node, int i); // ls -l -r
t_lst						*ft_time_sort(t_lst *node); // ls -t
t_lst						*ft_ascii_sort(t_lst *file);
void						ft_sort_options(t_lst *node, t_opt *opt); // char *path);

#endif
