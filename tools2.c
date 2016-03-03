/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:23:13 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/03 16:35:09 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_put_link(char *path)
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

char	*ft_get_pathname(t_lst *node, char *pathname)
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

void	ft_error(char *path)
{
	ft_putstr("ft_ls: ");
	perror(path);
}

void	ft_error_rights(t_lst *node, char *path)
{
	if (node->file_data->get_perm[0] == 'd'
			&& node->file_data->get_perm[1] == '-')
	{
		ft_putstr("ft_ls: ");
		ft_putstr(path);
		ft_putendl(": Permission denied");
		return ;
	}
}
