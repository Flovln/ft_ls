/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:18:26 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/19 18:07:49 by fviolin          ###   ########.fr       */
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

char			*ft_remove_slash(char *path)
{
	int len;

	len = ft_strlen(path);
	path[len - 1] = '\0';
	return (path);
}

void			ft_read_param(char *path, t_opt *options)
{
	DIR				*dir;
	struct dirent	*ret;
	t_lst			*node;
	t_pad			*pad;
	int				is_file;

	is_file = 0;
	pad = (t_pad *)malloc(sizeof(t_pad));
	if (!(node = (t_lst *)malloc(sizeof(t_lst))))
		exit(1);
	node = NULL;
	if (!(dir = opendir(path)))
	{
		node = manage_av_file(path, node, dir);
		if (node == NULL)
		{
			ft_putstr("ft_ls: ");
			perror(path);
			return ;
		}
		is_file = 1;
	}
	else if (is_file == 0)
	{
		path = ft_add_slash(path);
		while ((ret = readdir(dir)))
			node = ft_get_data(node, ret->d_name,
					ft_strjoin(path, ret->d_name));
		closedir(dir);
	}
	ft_padding(&node, pad); //general padding
	ft_sort_options(node, options, path); //options managing
}

int				main(int ac, char **av)
{
	int		i;
	char	*path;
	t_opt	opt;

	i = 0;
	path = NULL;
	ft_init_opt(&opt);
	if (!ft_strcmp("''", av[i]) || !ft_strcmp("""", av[i]))
	{
//		ft_putstr("AAAA\n");
		ft_putendl_fd("ft_ls: fts_open: No such file or directory", 2);
		exit(1);
	}
	while (++i < ac)
	{
		if (av[i][0] == '-')
			ft_options(av[i], &opt);
		else
		{
			path = av[i];
			ft_read_param(path, &opt);
		}
	}
	if (!path)
		ft_read_param("./", &opt);
	return (0);
}
