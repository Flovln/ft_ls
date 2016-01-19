/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 12:21:06 by fviolin           #+#    #+#             */
/*   Updated: 2016/01/19 17:22:26 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	int	ft_count_obj(struct dirent *read)
{
	int count;

	count = 0;
/*si le repertoire contient un '.' dans son nom, alors on ne l'affiche pas */
	if (ft_strncmp(read->d_name, ".", 1) != 0)
	{
		ft_putendl(read->d_name); // = ft_putstr + rajoute \n a la fin
		count++;
	}
	return (count);
}

int		main()
{
	int				files;
	struct dirent	*read;
	struct stat		st;
	DIR				*dir_ptr;

	read = NULL;
	dir_ptr = NULL;
	dir_ptr = opendir(".");
	//else
  	if (dir_ptr == NULL)
   		return (1);
	printf("Success opening file\n");
	while ((read = readdir(dir_ptr)) != NULL)
		files += ft_count_obj(read);
/* s'il y a un soucis avec la fermeture */
	if (closedir(dir_ptr) == -1)
		return (-1);
	printf("Success closing file\n");
}
