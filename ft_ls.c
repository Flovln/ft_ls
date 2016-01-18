/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 12:21:06 by fviolin           #+#    #+#             */
/*   Updated: 2016/01/18 13:19:46 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	int	ft_count_obj(struct dirent *rd, struct stat *st)
{
	int count;

	count = 0;
	if (ft_strcmp(rd->d_name, ".") != 0 && ft_strcmp(rd->d_name , "..") != 0)
	{
		ft_putendl(rd->d_name);
		count++;
	}
	return (count);
}

int		main()
{
	int				files;
	struct dirent	*rd;
	struct stat		st;
	DIR				*dirp;

	rd = NULL;
	dirp = NULL;
	dirp = opendir(".");
	//else
  	if (dirp == NULL)
   		return (1);
	printf("Success opening file\n");
	while ((rd = readdir(dirp)) != NULL)
	{
		files += ft_count_obj(rd, &st);
//		printf("Success reading file\n");
	}
	if (closedir(dirp) == -1)
		return (-1);
	printf("Success closing file\n");
}
