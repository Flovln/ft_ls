/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:01:09 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/03 10:53:43 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_perm_acc(t_lst *elem, struct stat *file_stat)
{
	ft_memset(elem->file_data->get_perm, 0, 11);
	elem->file_data->get_perm[0] = (S_ISDIR(file_stat->st_mode)) ? 'd' : '-'; // d = Directory / '-' = file
	elem->file_data->get_perm[1] = (file_stat->st_mode & S_IRUSR) ? 'r' : '-'; // read permission, owner
	elem->file_data->get_perm[2] = (file_stat->st_mode & S_IWUSR) ? 'w' : '-'; // write permission, owner
	elem->file_data->get_perm[3] = (file_stat->st_mode & S_IXUSR) ? 'x' : '-'; // execute/search permission, owner
	elem->file_data->get_perm[4] = (file_stat->st_mode & S_IRGRP) ? 'r' : '-'; // read permission, group
	elem->file_data->get_perm[5] = (file_stat->st_mode & S_IWGRP) ? 'w' : '-'; // write permission, group
	elem->file_data->get_perm[6] = (file_stat->st_mode & S_IXGRP) ? 'x' : '-'; // execute/search permission, group
	elem->file_data->get_perm[7] = (file_stat->st_mode & S_IROTH) ? 'r' : '-'; // read permission, other/world
	elem->file_data->get_perm[8] = (file_stat->st_mode & S_IWOTH) ? 'w' : '-'; // write permission, other/world
	elem->file_data->get_perm[9] = (file_stat->st_mode & S_IXOTH) ? 'x' : '-'; // execute/search permission, other/world
}

void	ft_add_data(struct stat file_stat, t_lst *node, char *file) // char *path)
{
	struct passwd	*user_name;
	struct group	*group_name;

	ft_perm_acc(node, &file_stat);
	node->file_data->links = ft_itoa(file_stat.st_nlink);
	if ((user_name = getpwuid(file_stat.st_uid)))
		node->file_data->uid = ft_strdup(user_name->pw_name);
	if ((group_name = getgrgid(file_stat.st_gid)))
		node->file_data->gid = ft_strdup(group_name->gr_name);
	node->file_data->size = ft_itoa(file_stat.st_size);
	node->date = ft_strsub(ctime(&file_stat.st_mtime), 4, 12);
	node->name = file;
}
