/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:23:13 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/03 11:26:28 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_put_link(char *path)
{
	char	buffer[1024];
	int		ret;

	ret = readlink(path, buffer, 1023);
	//if (ret == -1)
	//  return ;
	buffer[ret] = '\0';
	ft_putstr(" -> ");
	ft_putstr(buffer);
}

void	ft_error(char *path)
{
	ft_putstr("ft_ls: ");
	perror(path);
}
