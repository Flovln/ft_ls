/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:18:26 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/05 13:43:16 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
static void		ft_read_current(char *path)
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
*/

static	void	display_list(t_lst **node)
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

static	void	ft_read_param(char *path)
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
	{
		node = ft_get_data(node, ret->d_name, ft_strjoin(path, ret->d_name));
	//	printf("NODE is %s\n", node->name);
	}
	ft_padding(&node, pad);
	ft_ascii_sort(node); //
	display_list(&node);
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
			i++;
		}
	}
	else
	//	ft_read_current(".");
		ft_read_param("./");
	return (0);
}
