/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 16:51:06 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/20 15:04:57 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*ft_strndup(char const *s1, size_t len)
{
	char *scpy;

	if (!(scpy = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	return (ft_strncpy(scpy, s1, len));
}

static char		*get_file_name(char *path)
{
	int		end;
	int		start;
	char	*tmp;

	end = ft_strlen(path) - 1;
	start = end;
	while (path[start] != '/' && start > 0)
		start--;
	if (start == 0)
		tmp = ft_strsub(path, start, end + 1);
	else
		tmp = ft_strsub(path, start + 1, end);
	return (tmp);
}

char			*format_path(char *path)
{
	int		i;
	char	*tmp;

	if (path)
	{
		i = ft_strlen(path) - 1;
		if (path[i] == '/')
			return (NULL);
		else
		{
			tmp = ft_strdup(path);
			while (tmp[i] != '/' && i > 0)
				i--;
			if (i == 0) // modif return(tmp)
				tmp = ft_strdup("./");
			else //modif return(tmp)
				tmp = ft_add_slash(ft_strndup(path, i));
			return (tmp);
		}
	}
	else
		return (NULL);
}
/*
static t_lst	*manage_av_file_bis(char *path, t_lst *lst, DIR *dir)
{
	char			*file_name;
	struct dirent	*ret;

	file_name = get_file_name(path);
	while ((ret = readdir(dir))) //read 
	{
		if ((ft_strcmp(ret->d_name, file_name) == 0))
		{
			lst = ft_get_data(lst, ret->d_name, path);
			break ;
		}
	}
	if (!lst)
		return (NULL);
	closedir(dir); // close
	return (lst);
}
*/
t_lst			*manage_av_file(char *path, t_lst *lst, DIR *dir)
{
	char			*formated;
	char			*file_name;
	struct dirent	*ret;

	formated = format_path(path); //ft_strdup ?
	if (!formated)
		return (NULL);
	if (!(dir = opendir(formated))) /* open */
	{
		ft_putstr("ft_ls: ");
		perror(path);
		return (NULL);
	}
	else
	{
		file_name = get_file_name(path);
		while ((ret = readdir(dir))) // read
		{
			if ((ft_strcmp(ret->d_name, file_name) == 0))
			{
				lst = ft_get_data(lst, ret->d_name, path);
				break ;
			}
		}
		if (!lst)
			return (NULL);
		closedir(dir); // close
		return (lst);
	}
	return (NULL);
}
