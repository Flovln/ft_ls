/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_stat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:21:33 by fviolin           #+#    #+#             */
/*   Updated: 2016/01/28 13:30:23 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Affiche les Permissions d'acces */

void			ft_permission_rights(struct stat file_stat)
{
	ft_putstr( (S_ISDIR(file_stat.st_mode)) ? "d" : "-"); // d = Directory / '-' = file
	ft_putstr( (file_stat.st_mode & S_IRUSR) ? "r" : "-"); // read permission, owner
	ft_putstr( (file_stat.st_mode & S_IWUSR) ? "w" : "-"); // write permission, owner
	ft_putstr( (file_stat.st_mode & S_IXUSR) ? "x" : "-"); // execute/search permission, owner
	ft_putstr( (file_stat.st_mode & S_IRGRP) ? "r" : "-"); // read permission, group
	ft_putstr( (file_stat.st_mode & S_IWGRP) ? "w" : "-"); // write permission, group
	ft_putstr( (file_stat.st_mode & S_IXGRP) ? "x" : "-"); // execute/search permission, group
	ft_putstr( (file_stat.st_mode & S_IROTH) ? "r" : "-"); // read permission, other/world
	ft_putstr( (file_stat.st_mode & S_IWOTH) ? "w" : "-"); // write permission, other/world
	ft_putstr( (file_stat.st_mode & S_IXOTH) ? "x" : "-"); // execute/search permission, other/world
}

/* Affiche le nombre de links */

void			ft_links_nb(struct stat file_stat)
{
	printf("%d", file_stat.st_nlink);
}

/* Affiche le nom du proprietaire du fichier cible */

void			ft_get_file_uid(struct stat file_stat) //, t_file_info *get_info)
{
	struct passwd *user_name;

	user_name = NULL;
	if ((user_name = getpwuid(file_stat.st_uid)) != NULL)
		ft_putstr(user_name->pw_name);
}

/* Affiche group name */

void			ft_get_group_name(struct stat file_stat)
{
	struct group *group_name;

	group_name = NULL;
	if ((group_name = getgrgid(file_stat.st_gid)) != NULL)
		ft_putstr(group_name->gr_name);
}

/* Affiche taille du fichier/dossier */

void			ft_get_file_size(struct stat file_stat)
{
	printf("%lld", file_stat.st_size);
}

/* Affiche la date et heure */

void			ft_get_time(struct stat file_stat)
{
	ft_putstr(ctime(&file_stat.st_mtime));
}

int		main(int ac, char **av)
{
	struct stat 	file_stat;
	struct dirent	*read;
	t_lst_info		*get_info;

	if (ac != 2)
		return (1);
	if (stat(av[1], &file_stat) < 0)
		return (1);
	ft_permission_rights(file_stat);
	ft_putchar('\t');
	ft_links_nb(file_stat);
	ft_putchar('\t');
	ft_get_file_uid(file_stat);
	ft_putchar('\t');
	ft_get_group_name(file_stat);
	ft_putchar('\t');
	ft_get_file_size(file_stat);
	ft_putchar('\t');
	ft_get_time(file_stat);
	ft_putchar('\n');
	return (0);
}
