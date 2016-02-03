/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:18:26 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/03 10:42:02 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
/*
   static void		ft_list_files(struct dirent *read)
   {
   if (ft_strncmp(read->d_name, ".", 1) != 0)
   ft_putendl(read->d_name);
   }
   */

static void		ft_read_param(char *path)
{
	DIR				*dir;
	struct dirent	*ret;
	t_lst			*node;
	t_lst			*head;
	t_pad			*pad;

	if (!(dir = opendir(path)))
	{
		ft_putendl("opening error");
		exit(EXIT_FAILURE);
	}
	pad = (t_pad *)malloc(sizeof(t_lst));
	node = (t_lst *)malloc(sizeof(t_lst));
	if (!node)
		return ;
	head = node;
	node->next = NULL;
	while ((ret = readdir(dir)))
	{
		node = ft_get_data(node, ret->d_name, ft_strjoin(path, ret->d_name));
		node = head;
	}
	ft_padding(node, pad);
	display_list(node);
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
		ft_read_param("./");
	return (0);
}
