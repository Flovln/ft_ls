/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:18:26 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/27 19:11:01 by fviolin          ###   ########.fr       */
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
	}
	if (options && options->l) //Segfault without padding w/ -R + -Rr /library ~/
		ft_padding(&node, pad);
	ft_sort_options(node, options, path);
	if (!options->R && !node->next) // free arguments passes en parametres 
		ft_free_list(&node);
	else if (!options->R && node) // opt->R = 0 (rep courant ou ../ etc..) 
		ft_free_list(&node);
}

int				main(int ac, char **av)
{
	int		i;
	int		put_space; //
	int		flag;
	char	*path;
	t_opt	opt;

	i = 1;
	flag = 1;
	put_space = 0; //
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
		if (ac > 1)
		{
			ft_arg_type(path); //
//			DEBUG //
			while (i < ac - flag)
			{
				path = av[i];
				if (ac - flag > 1 && ft_arg_type(path) == 1) //
				{ 
					if (put_space != 0)
						ft_putchar('\n');
					ft_putstr(path);
					ft_putendl(":");
				} ///
				ft_read_param(path, &opt);
				i++;
				put_space = 1; //
			}
		}
	}
	if (!path)
		ft_read_param("./", &opt);
	else
		ft_free_tab(av);
	return (0);
}
