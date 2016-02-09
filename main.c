/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:18:26 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/09 17:30:38 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_display_curr(char *path) // ls command
{
	DIR				*dir;
	struct dirent	*ret;

	if (!(dir = opendir(path)))
		return ;
	while ((ret = readdir(dir)))
	{
		if (ft_strncmp(ret->d_name, ".", 1) != 0)
			ft_putendl(ret->d_name);
	}
	closedir(dir);
}


void		ft_display_l(t_lst **node) // ls -l command
{
	t_lst	*tmp;

	tmp = *node;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			ft_putstr("total ");
			ft_putstr(tmp->file_data->blocks);
			ft_putstr("\n");
		}
		tmp = tmp->next;
	}
	tmp = *node;
	display_data(tmp);
}

static	void	ft_read_param(char *path) //, int options)
{
	DIR				*dir;
	struct dirent	*ret;
	t_lst			*node;
	t_pad			*pad;

	if (!(dir = opendir(path)))
	{
		ft_putendl("opening error");
		exit(EXIT_FAILURE);
	}
	pad = (t_pad *)malloc(sizeof(t_pad));
	if (!(node = (t_lst *)malloc(sizeof(t_lst))))
		exit(EXIT_FAILURE);
	node = NULL;
	while ((ret = readdir(dir)))
		node = ft_get_data(node, ret->d_name, ft_strjoin(path, ret->d_name));
	ft_padding(&node, pad);// ls -l
	ft_ascii_sort(node); //
	ft_display_l(&node); // ls -l
//	ft_sort_options(node, options); //, path);
	closedir(dir);
}

int				main(int ac, char **av)
{
	int 	i;
//	t_opt	options;

	i = 0;
	if (ac > 1)
	{
		i = 1;
		while (av[i])
		{
			ft_read_param(av[i]);
			i++;
		}
	}
	else
		ft_read_param("./");
	return (0);
}
/*
int				main(int ac, char **av)
{
	int 	i;
	char	*path;
	t_opt	options;

	i = 0;
	path = NULL;
	ft_init_opt(&options);
	while (i < ac)
	{
		if (av[1][0] == '-')
		{
			while (av[i][0] == '-')
			{
				ft_options(av[i], options);
				i++;
			}
		}
		else
		{
			path = av[i];
			ft_read_param(path);
		}
		i++;
	}
	if (path == NULL)
		ft_display_curr(path);		
}
