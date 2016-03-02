/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 14:53:50 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/02 16:01:08 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_arg_type(char *tab)
{
	DIR			*dir;
	struct stat	st;

	if ((dir = opendir(tab)))
	{
		closedir(dir);
		return (1);
	}
	else if (!stat(tab, &st))
		return (0);
	else
		return (-1);
}

void		ft_sort_tab(char **tab, t_opt *opt, int flag)
{
	int i;

	i = 0;
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

char		**ft_create_tab(char **av, t_opt *opt, int ac, int flag)
{
	int		i;
	int		j;
	char	**tab;

	i = flag - 1;
	j = 0;
	ft_sort_tab(av, opt, flag);
	if (!(tab = (char **)malloc(sizeof(char *) * ac + 1)))
		return (NULL);
	while (++i < ac)
		if (ft_arg_type(av[i]) == -1)
			tab[j++] = ft_strdup(av[i]);
	i = flag - 1;
	while (++i < ac)
		if (ft_arg_type(av[i]) == 0)
			tab[j++] = ft_strdup(av[i]);
	i = flag - 1;
	while (++i < ac)
		if (ft_arg_type(av[i]) == 1)
			tab[j++] = ft_strdup(av[i]);
	tab[j] = NULL;
	return (tab);
}
