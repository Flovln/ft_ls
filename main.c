/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:18:26 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/21 19:21:46 by fviolin          ###   ########.fr       */
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

void			ft_init_opt(t_opt *opt)
{
	opt->l = 0;
	opt->R = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
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
		if (!node)
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
		//ft_putchar('\n'); // WRONG
	}
	ft_padding(&node, pad); //general padding
	ft_sort_options(node, options, path); //options managing
}

int				main(int ac, char **av)
{
	int		i;
	int		flag;
	char	*path;
	t_opt	opt;

	i = 1;
	flag = 1;
	path = NULL;
	ft_init_opt(&opt);
	if (ac > 1)
	{
		while (av[i] && av[i][0] == '-')
		{
			ft_options(av[i], &opt);
			flag++;
			i++;
		}
		if (ac > flag)
			av = ft_create_tab(av, &opt, ac, flag);
		i = 0;
		if (ac > 2)
		{
			while (i < ac - flag)
			{
				path = av[i];
				ft_read_param(path, &opt);
				i++;
			}
		}
	}
	if (!path)
		ft_read_param("./", &opt);
	return (0);
}
