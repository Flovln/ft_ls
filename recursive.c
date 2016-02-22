/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:28:41 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/22 14:08:06 by fviolin          ###   ########.fr       */
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
//	ft_read_param(ft_strjoin(path, ft_add_slash(all_d[i])), opt);
}

static void		ft_recursive_r(t_opt *opt, char *path, int nb_d, char **all_d)
{
	int		j;
	int		i;

	if (opt->r == 0)
	{
		i = -1;
		while (++i < nb_d)
		{
			if (all_d[i])
			{
				ft_put_css('\n', ft_strjoin(path, all_d[i]), ":\n");
				ft_read_param(ft_strjoin(path, ft_add_slash(all_d[i])), opt);
			}
		}
	}
	else if (opt->r == 1)
	{
		j = nb_d;
		while (--j > -1)
		{
			if (all_d[j])
			{
				ft_put_css('\n', ft_strjoin(path, all_d[j]), ":\n");
				ft_read_param(ft_strjoin(path, ft_add_slash(all_d[j])), opt);
			}
		}
	}
}

void			ft_recursive(t_lst *node, t_opt *opt, char *path, int nb_dir)
{
	char	**all_dir;
	int		i;

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
	ft_recursive_r(opt, path, nb_dir, all_dir);
}
