/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:18:26 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/08 17:16:44 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_check_void_av(int ac, char **av, int flag)
{
	int i;

	i = 0;
	while (i < ac - flag)
	{
		if (!ft_strcmp(av[i], ""))
		{
			ft_putendl("ft_ls: fts_open: No such file or directory");
			exit(0);
		}
		i++;
	}
}

static void		ft_put_path(char *path, int ac, int flag, int put_space)
{
	if (ac - flag > 1 && ft_arg_type(path) == 1)
	{
		if (put_space != 0)
			ft_putchar('\n');
		ft_putstr(path);
		ft_putendl(":");
	}
}

static int		ft_opt_check(char **av, t_opt *opt, int flag)
{
	int i;

	i = 1;
	while (av[i] && av[i][0] == '-' && av[i][1])
	{
		ft_options(av[i], opt);
		flag++;
		i++;
	}
	return (flag);
}

static void		ft_get_args(int ac, char *path, int flag, t_opt *opt)
{
	int i;

	i = 0;
	ft_put_path(path, ac, flag, i);
	if (i == 0)
		i = 1;
	ft_read_param(path, opt);
}

int				main(int ac, char **av)
{
	int		i;
	int		flag;
	char	*path;
	t_opt	opt;

	flag = 1;
	path = NULL;
	ft_init_opt(&opt);
	if (ac > 1)
	{
		flag = ft_opt_check(av, &opt, flag);
		if (ac > flag)
			av = ft_create_tab(av, &opt, ac, flag);
		i = -1;
		ft_check_void_av(ac, av, flag);
		while (++i < ac - flag && (path = av[i]))
			ft_get_args(ac, path, flag, &opt);
	}
	if (!path)
		ft_read_param("./", &opt);
	else
		ft_free_tab(av);
	return (0);
}
