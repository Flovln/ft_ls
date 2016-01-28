/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 11:20:12 by fviolin           #+#    #+#             */
/*   Updated: 2016/01/28 18:30:53 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


void		ft_get_rights(t_lst_info *get_stat, struct stat file_stat)
{
	ft_memset(get_stat->file_data->access_perm, 0, 11);
	get_stat->file_data->get_rights[0] = (S_ISDIR(file_stat.st_mode)) ? "d" : "-"; // d = Directory / '-' = file
	get_stat->file_data->get_rights[1] = (file_stat.st_mode & S_IRUSR) ? "r" : "-"; // read permission, owner
	get_stat->file_data->get_rights[2] = (file_stat.st_mode & S_IWUSR) ? "w" : "-"; // write permission, owner
	get_stat->file_data->get_rights[3] = (file_stat.st_mode & S_IXUSR) ? "x" : "-"; // execute/search permission, owner
	get_stat->file_data->get_rights[4] = (file_stat.st_mode & S_IRGRP) ? "r" : "-"; // read permission, group
	get_stat->file_data->get_rights[5] = (file_stat.st_mode & S_IWGRP) ? "w" : "-"; // write permission, group
	get_stat->file_data->get_rights[6] = (file_stat.st_mode & S_IXGRP) ? "x" : "-"; // execute/search permission, group
	get_stat->file_data->get_rights[7] = (file_stat.st_mode & S_IROTH) ? "r" : "-"; // read permission, other/world
	get_stat->file_data->get_rights[8] = (file_stat.st_mode & S_IWOTH) ? "w" : "-"; // write permission, other/world
	get_stat->file_data->get_rights[9] = (file_stat.st_mode & S_IXOTH) ? "x" : "-"; // execute/search permission, other/world
}

t_lst_info	*ft_stat(struct dirent *ret, struct stat *file_stat)
{
	DIR			*dir;
	t_lst_info	*head;
	t_lst_info	*node;

	dir = NULL;
	head = NULL;
	node = NULL;
	ret = NULL;
	dir = opendir(".");
	if (dir == NULL)
		return (1);
	while ((ret = readdir(dir)) != NULL)
	{
		node = ft_create_lst(ret, file_stat);
		ft_add_data(node, file_stat);
		ft_new_node(&head, node);
		node->name = ret->d_name;
	}
	closedir(dir);
}
