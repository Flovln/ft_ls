/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 11:41:51 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/02 18:03:22 by fviolin          ###   ########.fr       */
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

#define DEBUG printf("%d: %s\n", __LINE__, __func__); /// ---DEBUG--- ////

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
	size_t					min;
	size_t					maj;
	size_t					maj_min;
}							t_pad;

typedef struct				s_data
{
	int						blocks;
	char					get_perm[11];
	char					*links;
	char					*uid;
	char					*gid;
	char					*size;
	char					*min;
	char					*maj;
	char					*maj_min;
}							t_data;

typedef struct				s_lst
{
	dev_t					st_rdev;
	t_data					*file_data;
	char					*date;
	int						is_dir;
	int						last_edit;
	char					*name;
	char					*path; //
	struct s_lst			*next;
}							t_lst;

void						ft_add_data(struct stat file_stat,
								t_lst *node, char *file);
void						ft_add_node(t_lst **head, t_lst *current,
								t_lst *new_node);
char						*ft_add_slash(char *path);
t_lst						*ft_get_data(t_lst *head, char *path, char *file);
void						ft_padding(t_lst **head, t_pad *pad);
void						ft_init_pad(t_pad *pad, t_lst **node);
int							ft_check_opt(t_opt *opt);
int							ft_valid_opt(char c);
int							ft_options(char *s, t_opt *opt);
void						ft_init_opt(t_opt *opt);
void						ft_display_data(t_lst **node);
void						ft_display_total(t_lst **node, int i);
void						ft_display_curr(t_lst *node, int i);
void						ft_display_l(t_lst *node, int i);
void						ft_display_r(t_lst **node, int i);
void						ft_display_t(t_lst **node);
void						ft_display_l_r(t_lst **node, int i);
t_lst						*ft_time_sort(t_lst *node);
t_lst						*ft_ascii_sort(t_lst *file);
void						ft_sort_options(t_lst *node, t_opt *opt,
								char *path);
void						ft_error_opt(char *s);
void						ft_free_data(t_lst **node);
void						ft_free_list(t_lst **node);
void						ft_free_tab(char **tab);
void						ft_recursive(t_lst *node, t_opt *opt,
								char *path); //, int nb_dir);
int							ft_count_dir(t_lst *node);
void						ft_read_param(char *path, t_opt *opt);
void						ft_color_name(t_lst *node);
int							ft_count_node(t_lst *node);
void						ft_tab_swap(char **s1, char **s2);
void						ft_sort_tab(char **tab, t_opt *opt, int flag);
char						**ft_create_tab(char **av, t_opt *opt,
								int ac, int flag);
char						*ft_remove_slash(char *path);
t_lst						*manage_av_file(char *path, t_lst *lst, DIR *dir);
char						*format_path(char *path);
int							ft_arg_type(char *tab);
char						*ft_lastword(char *s);
void						ft_error(char *path);

#endif
