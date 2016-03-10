/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:18:26 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/10 14:57:45 by fviolin          ###   ########.fr       */
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
			ft_putendl_fd("ft_ls: fts_open: No such file or directory", 2);
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
		if ((i = -1) && ac > flag)
			av = ft_create_tab(av, &opt, ac, flag);
		ft_check_void_av(ac, av, flag);
		while (++i < ac - flag && (path = av[i]))
		{
			ft_put_path(path, ac, flag, i);
			ft_read_param(path, &opt);
		}
	}
	if (!path)
		ft_read_param("./", &opt);
	else
		ft_free_tab(av);
	return (0);
}
