/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_stat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:21:33 by fviolin           #+#    #+#             */
/*   Updated: 2016/01/27 17:50:39 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Afficher les Permissions d'acces */

void			ft_permission_rights(struct stat file_stat)
{
	ft_putstr( (S_ISDIR(file_stat.st_mode)) ? "d" : "-"); // d = Directory / '-' = file
	ft_putstr( (file_stat.st_mode & S_IRUSR) ? "" : "-"); // read permission, owner
	ft_putstr( (file_stat.st_mode & S_IWUSR) ? "w" : "-"); // write permission, owner
	ft_putstr( (file_stat.st_mode & S_IXUSR) ? "x" : "-"); // execute/search permission, owner
	ft_putstr( (file_stat.st_mode & S_IRGRP) ? "r" : "-"); // read permission, group
	ft_putstr( (file_stat.st_mode & S_IWGRP) ? "w" : "-"); // write permission, group
	ft_putstr( (file_stat.st_mode & S_IXGRP) ? "x" : "-"); // execute/search permission, group
	ft_putstr( (file_stat.st_mode & S_IROTH) ? "r" : "-"); // read permission, other/world
	ft_putstr( (file_stat.st_mode & S_IWOTH) ? "w" : "-"); // write permission, other/world
	ft_putstr( (file_stat.st_mode & S_IXOTH) ? "x" : "-"); // execute/search permission, other/world
}

/* Afficher le nom du proprietaire du fichier cible */

void			ft_get_file_uid(struct stat file_stat) //, t_file_info *get_info)
{
	struct passwd *user_name;

	user_name = NULL;
	if ((user_name = getpwuid(file_stat.st_uid)) != NULL)
		ft_putstr(user_name->pw_name);
		ft_putchar('\n');
}

/* Afficher le nom du Fichier */

void		ft_get_file_name(struct dirent *get_name)
{
	ft_putstr(get_name->d_name);
}

int		main(int ac, char **av)
{
	DIR				*dir_ptr;
	struct stat 	file_stat;
	struct dirent	*read;
	t_file_info		*get_info;

	dir_ptr = opendir(".");
	if (ac != 2)
		return (1);
	while ((read = readdir(dir_ptr)) != NULL)
	{
		if (stat(av[1], &file_stat) < 0)
			return (1);
		ft_permission_rights(file_stat);
		ft_putchar('\t');
		ft_get_file_uid(file_stat);
		ft_putchar('\t');
		ft_get_file_name(read);
		ft_putchar('\t');
	}
	closedir(dir_ptr);
	return (0);
}
