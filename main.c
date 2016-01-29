/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:18:26 by fviolin           #+#    #+#             */
/*   Updated: 2016/01/29 12:09:35 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_list_files(struct dirent *read)
{
	if (ft_strncmp(read->d_name, ".", 1) != 0)
		ft_putendl(read->d_name);
}

static void		ft_read_param(char *path)
{
	DIR				*dir;
	struct dirent	*ret;

	if (!(dir = opendir(path)))
	{
		ft_putendl("opening error");
		exit(EXIT_FAILURE);
	}
	while ((ret = readdir(dir)))
		ft_list_files(ret);
	closedir(dir);
}

int				main(int ac, char **av)
{
	int i;

	if (ac > 1)
	{
		i = 1;
		while (av[i])
		{
			ft_read_param(av[i]);
			ft_putchar('\n');
			i++;
		}
	}
	else
		ft_read_param(".");
	return (0);
}
