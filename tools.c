/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 15:15:35 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/22 14:55:00 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_color_name(t_lst *node)
{
	if (node->file_data->get_perm[0] == 'd')
		ft_putstr(GREEN);
	else if (node->file_data->get_perm[0] == 'l')
		ft_putstr(RED);
	else if (node->file_data->get_perm[0] == 'c')
		ft_putstr(BLUE);
	else if (node->file_data->get_perm[0] == 'b')
		ft_putstr(MAGENTA);
	ft_putstr(node->name);
	ft_putstr(COLOR_RESET);
}

char		*ft_add_slash(char *path)
{
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	return (path);
}

char		*ft_remove_slash(char *path)
{
	int len;

	len = ft_strlen(path);
	path[len - 1] = '\0';
	return (path);
}

void		ft_tab_swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void		ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
}

void 	ft_free_data(t_lst **node)
{
	if ((*node)->file_data->links)
		ft_strdel(&(*node)->file_data->links);
	if ((*node)->file_data->uid)
		ft_strdel(&(*node)->file_data->uid);
	if ((*node)->file_data->gid)
		ft_strdel(&(*node)->file_data->gid);
	if ((*node)->file_data->size)
		ft_strdel(&(*node)->file_data->size);
	if ((*node)->file_data->min)
		ft_strdel(&(*node)->file_data->min);
	if ((*node)->file_data->maj)
		ft_strdel(&(*node)->file_data->maj);
	if ((*node)->file_data->maj_min)
		ft_strdel(&(*node)->file_data->maj_min);
	if ((*node)->date)
		ft_strdel(&(*node)->date);
	if ((*node)->name)
		ft_strdel(&(*node)->name);
//	(*node)->file_data->blocks = 0;
}

void	ft_free_list(t_lst **node)
{
	int i;// test printf

	i = 0;// test
	while (*node)
	{
//		printf("Node freed nb = |%d|  name : %s\n", i, (*node)->name);
		ft_free_data(node);
		*node = (*node)->next;
		i++; //test 
	}
	free((*node));
	node = NULL;
}
