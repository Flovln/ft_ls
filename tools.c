/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 15:15:35 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/08 16:42:47 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_lastword(char *s)
{
	char	*ptr;
	int		is_word;

	ptr = NULL;
	is_word = 0;
	while (*s)
	{
		if (!ft_isspace(*s) && !is_word)
		{
			ptr = s;
			is_word = 1;
		}
		else if (ft_isspace(*s))
			is_word = 0;
		++s;
	}
	return (ptr);
}

void		ft_putstr_s(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	ft_putstr(" ");
}

char		*ft_add_slash(char *path)
{
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	return (path);
}

char		*ft_remove_slash(char *path)
{
	if (path[ft_strlen(path) - 1] == '/')
		path[ft_strlen(path) - 1] = '\0';
	return (path);
}

void		ft_tab_swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}
