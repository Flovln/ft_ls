/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arg_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 14:19:16 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/11 20:12:23 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		**sort_time(int start, int end, char **name, int *time[])
{
	int		i;

	i = start - 1;
	if (end - start > 1)
	{
		while (start < end - 1 && time[0][start + 1])
		{
			if (time[0][start] < time [0][start + 1])
			{
				ft_swap_string(time, name, start, 0);
				start = i;
			}
			else if (time[0][start] == time[0][start + 1])
			{
				if (time[1][start] < time[1][start + 1])
				{
					ft_swap_string(time, name, start, 1);
					start = i;
				}
			}
			start++;
		}
	}
	return (name);
}

static int		while_is_error(char **tab, char **cpy_name, int *time[])
{
	int i;

	i = 0;
	if (ft_arg_type(tab[i]) == -1)
		while (tab[i] && ft_arg_type(tab[i]) == -1)
		{
			cpy_name[i] = ft_strdup(tab[i]);
			time[0][i] = 0;
			time[1][i] = 0;
			i++;
		}
	return (i);
}

static int		while_is_file(char **tab, char **cpy_name, int *time[], int i)
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
			time[0][i] = (int)st.st_mtime;
			time[1][i] = (int)st.TIMENSEC;
			i++;
		}
	end = i;
	cpy_name[i] = NULL;
	cpy_name = sort_time(start, end, cpy_name, time);
	return (i);
}

static int		while_is_dir(char **tab, char **cpy_name, int *time[], int i)
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
			time[0][i] = (int)st.st_mtime;
			time[1][i] = (int)st.TIMENSEC;
			closedir(dir);
			i++;
		}
	cpy_name[i] = NULL;
	cpy_name = sort_time(start, i, cpy_name, time);
	return (i);
}

char			**ft_sort_tab_time(char **tab, int len)
{
	int		i;
	char	**cpy_name;
	int		*cpy_date[2];

	i = 0;
	if (!(cpy_name = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	cpy_date[0] = (int *)malloc(sizeof(int) * (len + 1));
	cpy_date[1] = (int *)malloc(sizeof(int) * (len + 1));
	i = while_is_error(tab, cpy_name, cpy_date);
	i = while_is_file(tab, cpy_name, cpy_date, i);
	i = while_is_dir(tab, cpy_name, cpy_date, i);
	free(cpy_date[0]);
	cpy_date[0] = NULL;
	free(cpy_date[1]);
	cpy_date[1] = NULL;
	return (cpy_name);
}
