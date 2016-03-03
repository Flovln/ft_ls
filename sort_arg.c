/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 14:53:50 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/03 15:36:23 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_arg_type(char *path)
{
	DIR			*dir;
	struct stat	st;

	if ((dir = opendir(path)))
	{
		closedir(dir);
		return (1);
	}
	else if (!stat(path, &st))
		return (0);
	else
		return (-1);
}

/*
 * * function time sort for args
 */
/*
void		ft_sort_time(char **tab)
{
	int		i;
	struct stat file_stat;

	i = 0;
	tab[i] = ft_get_time(&file_stat.st_mtime);
	while (tab[i + 1])
	{
		printf("tab[i] = |%s|\n", tab[i]);
		printf("tab[i + 1] = |%s|\n", tab[i + 1]);
		if (tab[i] > tab[i + 1])
			ft_tab_swap(&tab[i], &tab[i + 1]);
		else if (&tab[i] < &tab[i + 1])
			ft_tab_swap(&tab[i], &tab[i + 1]);
		i++;
	}
}
*/
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
//	if (opt->t)
//		ft_sort_time(tab); //
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
