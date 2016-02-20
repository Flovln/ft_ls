/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 15:15:35 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/20 18:57:17 by fviolin          ###   ########.fr       */
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

void		ft_sort_tab(char **tab, t_opt *opt, int flag)
{
	int i;

	i = 1;
	if (flag > 0)
		i += flag;
	while (tab[i + 1] != NULL)
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0 && opt->r == 0)
		{
			ft_tab_swap(tab + i, tab + i + 1);
			ft_sort_tab(tab, opt, flag);
		}
		else if (ft_strcmp(tab[i], tab[i + 1]) < 0 && opt->r == 1)
		{
			ft_tab_swap(tab + i, tab + i + 1);
			ft_sort_tab(tab, opt, flag);
		}
		i++;
	}
}
