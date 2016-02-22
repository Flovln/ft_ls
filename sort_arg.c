/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 14:53:50 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/22 14:59:05 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_arg_type(char *tab)
{
	DIR			*dir;
	struct stat	st;

	if ((dir = opendir(tab)))
	{
		closedir(dir);
		return (1); // is dir
	}
	else if (!stat(tab, &st))
		return (0); // is file
	else
		return (-1); // is none (is an error)
}

/* tri les arguments passes en parametre suivant la ou les options choisies */

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

/* tableau pour stocker et trier les arguments passes en parametre */

char		**ft_create_tab(char **av, t_opt *opt, int ac, int flag)
{
	int		i;
	int		j;
	char	**tab;

	i = flag;
	j = 0;
	ft_sort_tab(av, opt, flag);
	if (!(tab = (char **)malloc(sizeof(char *) * ac + 1)))
		return (NULL);
	while (i < ac)
	{
		if (ft_arg_type(av[i]) == -1)
		{
			tab[j] = ft_strdup(av[i]);
			j++;
		}
		i++;
	}
	i = flag;
	while (i < ac)
	{
		if (ft_arg_type(av[i]) == 0)
		{
			tab[j] = ft_strdup(av[i]);
			j++;
		}
		i++;
	}
	i = flag;
	while (i < ac)
	{
		if (ft_arg_type(av[i]) == 1)
		{
			tab[j] = ft_strdup(av[i]);
			j++;
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}
