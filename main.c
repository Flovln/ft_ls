/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:18:26 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/10 16:40:22 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_add_slash(char *path)
{
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	return (path);
}

void		ft_display_curr(t_lst **node) // ls command
{
	while (*node)
	{
		if (ft_strncmp((*node)->name, ".", 1) != 0)
			ft_putendl((*node)->name);
		*node = (*node)->next;
	}
}

void		ft_display_l(t_lst **node) // ls -l command
{
	t_lst	*head;

	head = *node;
	while (*node)
	{
		if ((*node)->next == NULL)
		{
			ft_putstr("total ");
			ft_putstr((*node)->file_data->blocks);
			ft_putstr("\n");
		}
		*node = (*node)->next;
	}
	*node = head;
	display_data(node);
}

void        ft_display_r(t_lst **node, int i) // ls -r command
{
	if (i == 0) //display all
	{
		if (*node)
		{
			ft_display_r(&(*node)->next, i);
				ft_putendl((*node)->name);
		}
	}
	else
	{
		if (*node) // doesn't display hidden files
		{
			ft_display_r(&(*node)->next, i);
			if (ft_strncmp((*node)->name, ".", 1))
				ft_putendl((*node)->name);
		}
	}
}

static	void	ft_read_param(char *path, t_opt *options)
{
	DIR				*dir;
	struct dirent	*ret;
	t_lst			*node;
	t_pad			*pad;

	if (!(dir = opendir(path)))
	{
		ft_putendl("opening error");
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
	int 	i;
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
