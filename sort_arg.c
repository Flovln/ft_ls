/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 14:53:50 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/08 16:41:18 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_sort_tab(char **tab, t_opt *opt, int flag)
{
	int i;

	i = 0;
	if (flag > 0)
		i += flag;
	while (tab[i + 1] != NULL)
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0 && opt->r == 0)
		{
			ft_tab_swap(&tab[i], &tab[i + 1]);
			ft_sort_tab(tab, opt, flag);
		}
		else if (ft_strcmp(tab[i], tab[i + 1]) < 0 && opt->r == 1)
		{
			ft_tab_swap(&tab[i], &tab[i + 1]);
			ft_sort_tab(tab, opt, flag);
		}
		i++;
	}
}

static char		**reverse_tab2(char **tab, char **cpy, int start, int i)
{
	int end;
	int ref;

	end = i - 1;
	ref = start;
	while (end >= ref)
	{
		cpy[start] = ft_strdup(tab[end]);
		end--;
		start++;
	}
	end = ft_tablen(tab) - 1;
	ref = i;
	while (end >= ref)
	{
		cpy[i] = ft_strdup(tab[end]);
		end--;
		i++;
	}
	cpy[i] = NULL;
	ft_free_tab(tab);
	return (cpy);
}

static char		**reverse_tab(char **tab)
{
	int		i;
	int		start;
	int		end;
	char	**cpy;

	i = 0;
	if (!(cpy = (char **)malloc(sizeof(char *) * (ft_tablen(tab) + 1))))
		return (NULL);
	while (ft_arg_type(tab[i]) == -1)
	{
		cpy[i] = ft_strdup(tab[i]);
		i++;
	}
	start = i;
	while (ft_arg_type(tab[i]) == 0)
		i++;
	end = i - 1;
	return (reverse_tab2(tab, cpy, start, i));
}

static void		ft_cpy_in_tab(int i, int ac, char **tab, char **av)
{
	int j;
	int ref;

	j = 0;
	ref = i;
	while (++i < ac)
		if (ft_arg_type(av[i]) == -1)
			tab[j++] = ft_strdup(av[i]);
	i = ref;
	while (++i < ac)
		if (ft_arg_type(av[i]) == 0)
			tab[j++] = ft_strdup(av[i]);
	i = ref;
	while (++i < ac)
		if (ft_arg_type(av[i]) == 1)
			tab[j++] = ft_strdup(av[i]);
	tab[j] = NULL;
}

char			**ft_create_tab(char **av, t_opt *opt, int ac, int flag)
{
	int		i;
	int		j;
	char	**tab;

	i = flag - 1;
	j = 0;
	if (opt && !opt->t)
		ft_sort_tab(av, opt, flag);
	if (!(tab = (char **)malloc(sizeof(char *) * (ac - flag + 1))))
		return (NULL);
	ft_cpy_in_tab(i, ac, tab, av);
	if (opt && opt->t && !opt->r)
		tab = ft_sort_tab_time(tab, ft_tablen(tab));
	if (opt && opt->t && opt->r)
		tab = reverse_tab(tab);
	return (tab);
}
