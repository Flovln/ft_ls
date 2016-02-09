/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:01:09 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/09 15:59:02 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	ft_perm_acc(t_lst *elem, struct stat *file_stat)
{
	ft_memset(elem->file_data->get_perm, 0, 11);
	elem->file_data->get_perm[0] = (S_ISDIR(file_stat->st_mode)) ? 'd' : '-';
	elem->file_data->get_perm[1] = (file_stat->st_mode & S_IRUSR) ? 'r' : '-';
	elem->file_data->get_perm[2] = (file_stat->st_mode & S_IWUSR) ? 'w' : '-';
	elem->file_data->get_perm[3] = (file_stat->st_mode & S_IXUSR) ? 'x' : '-';
	elem->file_data->get_perm[4] = (file_stat->st_mode & S_IRGRP) ? 'r' : '-';
	elem->file_data->get_perm[5] = (file_stat->st_mode & S_IWGRP) ? 'w' : '-';
	elem->file_data->get_perm[6] = (file_stat->st_mode & S_IXGRP) ? 'x' : '-';
	elem->file_data->get_perm[7] = (file_stat->st_mode & S_IROTH) ? 'r' : '-';
	elem->file_data->get_perm[8] = (file_stat->st_mode & S_IWOTH) ? 'w' : '-';
	elem->file_data->get_perm[9] = (file_stat->st_mode & S_IXOTH) ? 'x' : '-';
}

void			ft_add_data(struct stat file_stat, t_lst *node, char *file) // char *path)
{
	struct passwd	*user_name;
	struct group	*group_name;
	static int		blocks;

	blocks += file_stat.st_blocks;
	node->file_data->blocks = ft_itoa(blocks);
	ft_perm_acc(node, &file_stat);
	node->file_data->links = ft_itoa(file_stat.st_nlink);
	if ((user_name = getpwuid(file_stat.st_uid)))
		node->file_data->uid = ft_strdup(user_name->pw_name);
	if ((group_name = getgrgid(file_stat.st_gid)))
		node->file_data->gid = ft_strdup(group_name->gr_name);
	node->file_data->size = ft_itoa(file_stat.st_size);
	node->date = ft_strsub(ctime(&file_stat.st_mtime), 4, 12);
	node->last_edit = (int)(file_stat.st_mtime); //time sort
	node->name = file;
	node->next = NULL;
}
