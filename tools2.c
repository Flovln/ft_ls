/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:23:13 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/11 20:12:33 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void            ft_swap_string(int *time[], char **name, int start, int j)
{
	int     itmp;
	char    *stmp;

	itmp = 0;
	itmp = time[j][start];
	time[j][start] = time[j][start + 1];
	time[j][start + 1] = itmp;
	stmp = name[start];
	name[start] = ft_strdup(name[start + 1]);
	name[start + 1] = ft_strdup(stmp);
}

void			ft_init_pad(t_pad *pad, t_lst **node)
{
	pad->links = ft_strlen((*node)->file_data->links);
	pad->uid = ft_strlen((*node)->file_data->uid);
	pad->gid = ft_strlen((*node)->file_data->gid);
	pad->size = ft_strlen((*node)->file_data->size);
	pad->min = ft_strlen((*node)->file_data->min);
	pad->maj = ft_strlen((*node)->file_data->maj);
	pad->maj_min = 0;
}

void			ft_put_link(char *path)
{
	char	buffer[1024];
	int		ret;

	ret = readlink(path, buffer, 1023);
	if (ret == -1)
		return ;
	buffer[ret] = '\0';
	ft_putstr(" -> ");
	ft_putstr(buffer);
}

char			*ft_get_pathname(t_lst *node, char *pathname)
{
	char	*tmp;

	if (pathname[ft_strlen(pathname) - 1] != '/')
	{
		tmp = ft_strjoin(pathname, "/");
		node->path = ft_strjoin(tmp, node->name);
		ft_strdel(&tmp);
	}
	else
		node->path = ft_strjoin(pathname, node->name);
	return (pathname);
}

int				ft_arg_type(char *path)
{
	DIR			*dir;
	struct stat	st;

	if ((dir = opendir(path)))
	{
		closedir(dir);
		return (1);
	}
	else if (!stat(path, &st))
		return (0);
	else
		return (-1);
}
