/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 16:51:06 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/11 20:11:55 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*ft_strndup(char const *s1, size_t len)
{
	char *scpy;

	if (!(scpy = (char *)malloc(sizeof(char) * (len + 1))))
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
			if (i == 0)
				tmp = ft_strdup("./");
			else
				tmp = ft_add_slash(ft_strndup(path, i));
			return (tmp);
		}
	}
	else
		return (NULL);
}

t_lst			*manage_av_file(char *path, t_lst *lst, DIR *dir)
{
	char			*formated;
	struct dirent	*ret;

	formated = format_path(path);
	if (!formated)
		return (NULL);
	if (!(dir = opendir(formated)))
	{
		ft_error(path);
		return (NULL);
	}
	else
	{
		while ((ret = readdir(dir)))
			if ((ft_strcmp(ret->d_name, get_file_name(path)) == 0))
			{
				lst = ft_get_data(lst, ret->d_name, path);
				break ;
			}
		if (!lst)
			return (NULL);
		closedir(dir);
		return (lst);
	}
	return (NULL);
}
