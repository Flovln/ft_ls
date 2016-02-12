/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:18:26 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/11 16:28:06 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_init_pad(t_pad *pad)
{
	pad->links = 0;
	pad->uid = 0;
	pad->gid = 0;
	pad->size = 0;
	pad->min = 0;
	pad->maj = 0;
}

char			*ft_add_slash(char *path)
{
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	return (path);
}

static char		*ft_remove_slash(char *path)
{
	int len;

	len = ft_strlen(path);
	path[len - 1] = '\0';
	return (path);
}

static	void	ft_read_param(char *path, t_opt *options)
{
	DIR				*dir;
	struct dirent	*ret;
	t_lst			*node;
	t_pad			*pad;

	if (!(dir = opendir(path)))
	{
		ft_putstr("ft_ls: ");
		perror(ft_remove_slash(path));
		return ;
	}
	pad = (t_pad *)malloc(sizeof(t_pad));
	if (!(node = (t_lst *)malloc(sizeof(t_lst))))
		exit(1);
	node = NULL;
	while ((ret = readdir(dir)))
		node = ft_get_data(node, ret->d_name, ft_strjoin(path, ret->d_name));
	closedir(dir);
	ft_padding(&node, pad); //general padding
	ft_sort_options(node, options); //options managing
}

int				main(int ac, char **av)
{
	int		i;
	char	*path;
	t_opt	options;

	i = 1;
	path = NULL;
	ft_init_opt(&options);
	while (i < ac)
	{
		if (av[i][0] == '-')
			ft_options(av[i], &options);
		else
		{
			path = av[i];
			ft_read_param(ft_add_slash(path), &options);
		}
		i++;
	}
	if (!path)
		ft_read_param("./", &options);
	return (0);
}
