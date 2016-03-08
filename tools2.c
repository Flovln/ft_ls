/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:23:13 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/08 17:19:19 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void			ft_init_opt(t_opt *opt)
{
	opt->l = 0;
	opt->maj_r = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
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
