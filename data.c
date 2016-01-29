/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:01:09 by fviolin           #+#    #+#             */
/*   Updated: 2016/01/29 16:15:18 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_perm_acc(t_lst_info *elem, struct stat *file_stat)
{
	ft_memset(elem->get_perm, 0, 11);
	elem->get_perm[0] = (S_ISDIR(file_stat->st_mode)) ? 'd' : '-'; // d = Directory / '-' = file
	elem->get_perm[1] = (file_stat->st_mode & S_IRUSR) ? 'r' : '-'; // read permission, owner
	elem->get_perm[2] = (file_stat->st_mode & S_IWUSR) ? 'w' : '-'; // write permission, owner
	elem->get_perm[3] = (file_stat->st_mode & S_IXUSR) ? 'x' : '-'; // execute/search permission, owner
	elem->get_perm[4] = (file_stat->st_mode & S_IRGRP) ? 'r' : '-'; // read permission, group
	elem->get_perm[5] = (file_stat->st_mode & S_IWGRP) ? 'w' : '-'; // write permission, group
	elem->get_perm[6] = (file_stat->st_mode & S_IXGRP) ? 'x' : '-'; // execute/search permission, group
	elem->get_perm[7] = (file_stat->st_mode & S_IROTH) ? 'r' : '-'; // read permission, other/world
	elem->get_perm[8] = (file_stat->st_mode & S_IWOTH) ? 'w' : '-'; // write permission, other/world
	elem->get_perm[9] = (file_stat->st_mode & S_IXOTH) ? 'x' : '-'; // execute/search permission, other/world
}
