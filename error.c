/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 16:13:00 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/08 16:37:08 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*get_path_error(char *path)
{
	int		i;
	int		j;
	int		end;
	char	*new;

	j = 0;
	path = ft_remove_slash(path);
	i = ft_strlen(path);
	end = i;
	while (i > 0 && path[i - 1] != '/')
		i--;
	new = ft_strnew(end - i + 1);
	while (path[i])
	{
		new[j] = path[i];
		i++;
		j++;
	}
	return (new);
}

int				ft_error(char *path)
{
	ft_putstr("ft_ls: ");
	path = get_path_error(path);
	perror(path);
	return (1);
}

int				ft_error_rights(t_lst *node, char *path)
{
	if (node->file_data->get_perm[0] == 'd'
			&& node->file_data->get_perm[1] == '-')
	{
		ft_putstr("ft_ls: ");
		ft_putstr(path);
		ft_putendl(": Permission denied");
		return (1);
	}
	return (0);
}
