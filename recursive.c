/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:28:41 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/27 19:10:53 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_count_dir(t_lst *node)
{
	int	i;

	i = 0;
	while (node)
	{
		if (node->is_dir)
			i++;
		node = node->next;
	}
	return (i);
}

static	void	ft_put_css(char c, char *s1, char *s2)
{
	ft_putchar(c);
	ft_putstr(s1);
	ft_putstr(s2);
}

void			ft_recursive(t_lst *node, t_opt *opt, char *path) //, int nb_dir)
{
	char	**all_dir;
	int		i;
	int		j;
	int		nb_dir;

	nb_dir = ft_count_dir(node);
	i = 0;
	if (!(all_dir = (char **)malloc(sizeof(char *) * nb_dir + 1)))
		exit(1);
	while (node)
	{
		if (node->is_dir == 1)
		{
			if (opt->a == 0 && node->name[0] != '.')
			{
				all_dir[i] = ft_strdup(node->name);
				i++;
			}
			else if (opt->a != 0)
			{
				all_dir[i] = ft_strdup(node->name);
				i++;
			}
		}
		node = node->next;
	}
	all_dir[i] = NULL;
	if (opt->r == 0)
	{
		i = -1;
		while (++i < nb_dir)
		{
			if (all_dir[i])
			{
				ft_put_css('\n', ft_strjoin(path, all_dir[i]), ":\n");
				ft_read_param(ft_strjoin(path, ft_add_slash(all_dir[i])), opt);
			}
		}
	}
	else if (opt->r == 1)
	{
		j = nb_dir - 1;
		while (j > -1)
		{
			if (all_dir[j])
			{
				ft_put_css('\n', ft_strjoin(path, all_dir[j]), ":\n");
				ft_read_param(ft_strjoin(path, ft_add_slash(all_dir[j])), opt);
			}
			j--;
		}
	}
//	ft_free_list(&node); // doesn't work
	opt->R = 1; // for free in ft_read_param
}
