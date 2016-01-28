/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 11:20:12 by fviolin           #+#    #+#             */
/*   Updated: 2016/01/28 14:18:16 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"


static void		stat_permission_rights(t_lst_info *get_stat, struct stat file_stat)
{
	ft_memset(get_stat->access_perm, 0, 11);
	get_stat->access_perm[0] = (S_ISDIR(file_stat.st_mode)) ? "d" : "-"; // d = Directory / '-' = file
	get_stat->access_perm[1] = (file_stat.st_mode & S_IRUSR) ? "r" : "-"; // read permission, owner
	get_stat->access_perm[2] = (file_stat.st_mode & S_IWUSR) ? "w" : "-"; // write permission, owner
	get_stat->access_perm[3] = (file_stat.st_mode & S_IXUSR) ? "x" : "-"; // execute/search permission, owner
	get_stat->access_perm[4] = (file_stat.st_mode & S_IRGRP) ? "r" : "-"; // read permission, group
	get_stat->access_perm[5] = (file_stat.st_mode & S_IWGRP) ? "w" : "-"; // write permission, group
	get_stat->access_perm[6] = (file_stat.st_mode & S_IXGRP) ? "x" : "-"; // execute/search permission, group
	get_stat->access_perm[7] = (file_stat.st_mode & S_IROTH) ? "r" : "-"; // read permission, other/world
	get_stat->access_perm[8] = (file_stat.st_mode & S_IWOTH) ? "w" : "-"; // write permission, other/world
	get_stat->access_perm[9] = (file_stat.st_mode & S_IXOTH) ? "x" : "-"; // execute/search permission, other/world
}

int				get_stat(void)
{
	return (0);
}
