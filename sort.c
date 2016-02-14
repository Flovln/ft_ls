/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 13:25:15 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/11 13:35:06 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_error_opt(char *s)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putendl_fd(s, 2);
	ft_putstr_fd("usage: ft_ls [-Ralrt] [file ...]\n", 2);
	exit(1);
}

t_lst			*ft_lst_swap(t_lst *node, t_lst *node_next)
{
	node->next = node_next->next;
	node_next->next = node;
	return (node_next);
}

t_lst			*ft_ascii_sort(t_lst *node)
{
	if (!node)
		return (NULL);
	if (node->next && ft_strcmp(node->name, node->next->name) > 0)
		node = ft_lst_swap(node, node->next);
	node->next = ft_ascii_sort(node->next);
	if (node->next && ft_strcmp(node->name, node->next->name) > 0)
	{
		node = ft_lst_swap(node, node->next);
		node->next = ft_ascii_sort(node->next);
	}
	return (node);
}

t_lst			*ft_time_sort(t_lst *node)
{
	if (!node)
		return (NULL);
	if (node->next && (node->last_edit < node->next->last_edit))
		node = ft_lst_swap(node, node->next);
	node->next = ft_time_sort(node->next); // recusive infix
	if (node->next && (node->last_edit < node->next->last_edit))
	{
		node = ft_lst_swap(node, node->next);
		node->next = ft_time_sort(node->next);
	}
	return (node);
}

int			ft_count_dir(t_lst *node)
{
	int		i;

	i = 0;
	while (node)
	{
		if (node->is_dir)
			i++;
		node = node->next;
	}
	return (i);
}
/*
static void			ft_putcss(char c, char *s1, char *s2) /////
{
	ft_putchar(c);
	ft_putstr(s1);
	ft_putstr(s2);
}

void			ft_recursive(char *path, t_lst *node, t_opt *opt, int nb_dir) /////
{
	char	**all_dir;
	int		i;

	i = 0;
	if (!(all_dir = (char **)malloc(sizeof(char *) * nb_dir + 1)))
		return ;
	*all_dir[nb_dir + 1] = '\0';
	while (node)
	{
		if (node->is_dir == 1)
		{
			all_dir[i] = ft_strdup(node->name);
			i++;
		}
		node = node->next;
	}
	i = -1;
	while (i < nb_dir)
	{
		if (opt && all_dir[i][0] == '.')
			ft_putcss('\n', ft_strjoin(path, all_dir[i]), ":\n");
		else if (all_dir[i][0] != '.')
			ft_putcss('\n', ft_strjoin(path, all_dir[i]), ":\n");
		ft_read_param(ft_strjoin(path, ft_add_slash(all_dir[i])), opt);			
		i++;
	}
}*/
