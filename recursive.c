/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:28:41 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/16 14:49:46 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int         ft_count_dir(t_lst *node)
{
	int     i;

	i = 0;
	while (node)
	{
		if (node->is_dir)
			i++;
		node = node->next;
	}
	return (i);
}

static void         ft_putcss(char c, char *s1, char *s2)
{
	ft_putchar(c);
	ft_putstr(s1);
	ft_putstr(s2);
}

void            ft_recursive(t_lst *node, t_opt *opt, char *path, int nb_dir)
{
	char    **all_dir;
	int     i;

	i = 0;
	if (!(all_dir = (char **)malloc(sizeof(char *) * nb_dir + 1)))
		exit(1);
	all_dir[nb_dir + 1] = NULL;
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
	while (++i < nb_dir)
	{
		if (opt->a && all_dir[i][0] == '.')
			ft_putcss('\n', ft_strjoin(path, all_dir[i]), ":\n");
		else if (all_dir[i][0] != '.')
			ft_putcss('\n', ft_strjoin(path, all_dir[i]), ":\n");
		ft_read_param(ft_strjoin(path, ft_add_slash(all_dir[i])), opt);
	}
}
