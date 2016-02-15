/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:28:41 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/15 13:30:25 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void         ft_putcss(char c, char *s1, char *s2) /////
{
	ft_putchar(c);
	ft_putstr(s1);
	ft_putstr(s2);
}

void            ft_recursive(char *path, t_lst *node, t_opt *opt, int nb_dir) /////
{
	char    **all_dir;
	int     i;

	i = 0;
	if (!(all_dir = (char **)malloc(sizeof(char *) * nb_dir + 1)))
		exit(1);
//  all_dir[nb_dir + 1] = '\0';
	while (node != NULL)
	{
		if (node->is_dir == 1)
		{
//          ft_putstr("DDDD\n");
			all_dir[i] = ft_strdup(node->name);
			i++;
		}
		node = node->next;
	}
	i = 0;
	while (++i < nb_dir)
	{
//      ft_putstr("AAAA\n");
		if (opt && opt->a && all_dir[i][0] == '.')
		{
//          ft_putstr("BBBB\n");
			ft_putcss('\n', ft_strjoin(path, all_dir[i]), ":\n");
		}
		else if (all_dir[i][0] != '.')
		{
//          ft_putstr("CCCC\n");
			ft_putcss('\n', ft_strjoin(path, all_dir[i]), ":\n");
		}
		ft_read_param(ft_strjoin(path, ft_add_slash(all_dir[i])), opt);
	}
}
