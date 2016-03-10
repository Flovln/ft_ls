/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arg_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 14:19:16 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/10 15:31:38 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		**sort_time(int start, int end, char **name, int *time)
{
	int		i;
	int		itmp;
	char	*stmp;

	itmp = 0;
	i = start;
	if (end - start > 1)
		while (start < end - 1)
		{
			if (time[start + 1] != 0)
			{
				if (time[start] < time[start + 1])
				{
					itmp = time[start];
					time[start] = time[start + 1];
					time[start + 1] = itmp;
					stmp = name[start];
					name[start] = ft_strdup(name[start + 1]);
					name[start + 1] = ft_strdup(stmp);
					start = i;
				}
			}
			start++;
		}
	return (name);
}

static int		while_is_error(char **tab, char **cpy_name, int *cpy_date)
{
	int i;

	i = 0;
	if (ft_arg_type(tab[i]) == -1)
		while (tab[i] && ft_arg_type(tab[i]) == -1)
		{
			cpy_name[i] = ft_strdup(tab[i]);
			cpy_date[i] = 0;
			i++;
		}
	return (i);
}

static int		while_is_file(char **tab, char **cpy_name, int *cpy_date, int i)
{
	int			end;
	int			start;
	struct stat	st;

	start = i;
	if (ft_arg_type(tab[i]) == 0)
		while (ft_arg_type(tab[i]) == 0)
		{
			stat(tab[i], &st);
			cpy_name[i] = ft_strdup(tab[i]);
			cpy_date[i] = (int)st.st_mtime;
			i++;
		}
	end = i;
	cpy_name[i] = NULL;
	cpy_name = sort_time(start, end, cpy_name, cpy_date);
	return (i);
}

static int		while_is_dir(char **tab, char **cpy_name, int *cpy_date, int i)
{
	struct dirent	*ret;
	struct stat		st;
	int				start;
	DIR				*dir;

	start = i;
	if (ft_arg_type(tab[i]) == 1)
		while (ft_arg_type(tab[i]) == 1)
		{
			dir = opendir(tab[i]);
			ret = readdir(dir);
			stat(tab[i], &st);
			cpy_name[i] = ft_strdup(tab[i]);
			cpy_date[i] = (int)st.st_mtime;
			closedir(dir);
			i++;
		}
	cpy_name[i] = NULL;
	cpy_name = sort_time(start, i, cpy_name, cpy_date);
	return (i);
}

char			**ft_sort_tab_time(char **tab, int len)
{
	int		i;
	char	**cpy_name;
	int		*cpy_date;

	i = 0;
	if (!(cpy_name = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	if (!(cpy_date = (int *)malloc(sizeof(int) * (len + 1))))
		return (NULL);
	i = while_is_error(tab, cpy_name, cpy_date);
	i = while_is_file(tab, cpy_name, cpy_date, i);
	i = while_is_dir(tab, cpy_name, cpy_date, i);
	free(cpy_date);
	cpy_date = 0;
	return (cpy_name);
}
