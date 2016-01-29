/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:18:26 by fviolin           #+#    #+#             */
/*   Updated: 2016/01/29 17:55:12 by fviolin          ###   ########.fr       */
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
	t_lst_info		*node;
	t_lst_info		*head;

	head = NULL;
	if (!(dir = opendir(path)))
	{
		ft_putendl("opening error");
		exit(EXIT_FAILURE);
	}
	node = (t_lst_info *)malloc(sizeof(t_lst_info));
	if (!node)
		return ;
	node->next = NULL;
	while ((ret = readdir(dir)))
	{
		node = ft_get_data(node, ret->d_name, ft_strjoin(path, ret->d_name)); //ret->d_name == char *file
		ft_new_node(&head, node);
		//node = node->next;
		ft_list_files(ret);
	}
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
