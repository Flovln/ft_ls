/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:28:41 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/07 18:34:56 by fviolin          ###   ########.fr       */
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
/* 
 * * opti pour norme
 */
static	void 	ft_cpy_dir_rec(t_lst *node, t_opt *opt, char **all_dir)
{
	int i;

	i = 0;
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
}

static void		ft_apply_r_rec(char **all_dir, char *path, int nb_dir, t_opt *opt)
{
	int j;

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

void			ft_recursive(t_lst *node, t_opt *opt, char *path)
{
	char	**all_dir;
	int		i;
	int		nb_dir;

	nb_dir = ft_count_dir(node);
	if (!(all_dir = (char **)malloc(sizeof(char *) * (nb_dir + 1))))
		exit(1);
	ft_cpy_dir_rec(node, opt, all_dir);
	if (opt->r == 0)
	{
		i = -1;
		while (++i < nb_dir)
			if (all_dir[i])
			{
				ft_put_css('\n', ft_strjoin(path, all_dir[i]), ":\n");
				ft_read_param(ft_strjoin(path, ft_add_slash(all_dir[i])), opt);
			}
			else
				break ;
	}
	else if (opt->r == 1)
		ft_apply_r_rec(all_dir, path, nb_dir, opt);
	//	ft_free_list(&node);
	ft_free_tab(all_dir);
	opt->R = 1;
}
