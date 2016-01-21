/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 12:21:06 by fviolin           #+#    #+#             */
/*   Updated: 2016/01/21 17:03:42 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
/*
t_file_info		*ft_init_file_info(t_file_info *get_info)
{
	get_info->mode = 0;
	get_info->size = 0;
	get_info-> uid = 0;
	get_info->gid = 0;
	return (get_info);
}
*/
static void		ft_file_stat(struct stat *get_stat, t_file_info *get_info)
{

	/*
	struct passwd *pwd;

	pwd = NULL;
	if ((pwd = getpwuid(get_stat->st_uid)) != NULL)
	{		
		get_info->uid = pwd->pw_name;
	}
	printf("Valeur uid : %s\n", get_info->uid);	*/
}

static void		ft_list_files(struct dirent *read_ptr)
{
	if (ft_strncmp(read_ptr->d_name, ".", 1) != 0)
		ft_putendl(read_ptr->d_name);
}

int		main(int ac, char **av)
{
	DIR				*dir_ptr;
	struct dirent	*read_ptr;
	struct stat		*get_stat; //path
	t_file_info		*get_info;

	dir_ptr = NULL;
	read_ptr = NULL;
	get_info = NULL;
	dir_ptr = opendir(".");
	if (dir_ptr == NULL)
		return (1);
	while ((read_ptr = readdir(dir_ptr)) != NULL)
	{
		if (stat(av[1], get_stat) > 0)
			return (1);
//		get_info = malloc(sizeof(t_file_info));
//		get_info = ft_init_file_info(get_info);
		ft_file_stat(get_stat, get_info);
		ft_list_files(read_ptr); //affiche les fichiers + dossiers du repertoire courant
	}
	closedir (dir_ptr);
	return (0);
}
