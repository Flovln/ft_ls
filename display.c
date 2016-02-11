/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 17:59:52 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/11 11:43:19 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void        ft_display_curr(t_lst **node, int i) // ls command
{
	if (i)
		while (*node) // ls
		{
			ft_putendl((*node)->name);
			*node = (*node)->next;
		}
	else
		while (*node) // -a
		{
			if (ft_strncmp((*node)->name, ".", 1) != 0)
				ft_putendl((*node)->name);
			*node = (*node)->next;
		}
}

void        ft_display_l(t_lst **node, int i) // ls -l + -a command
{
	ft_display_total(node);
	if (i == 1) // -a
		while (*node)
		{
			ft_display_data(node);
			*node = (*node)->next;
		}
	else // -l
		while (*node)
		{
			if (ft_strncmp((*node)->name, ".", 1) != 0)
				ft_display_data(node);
			*node = (*node)->next;
		}
}

void        ft_display_r(t_lst **node, int i) // ls -r command
{
	if (i == 1) // '-a'
	{
		if (*node)
		{
			ft_display_r(&(*node)->next, i);
			ft_putendl((*node)->name);
		}
	}
	else
		if (*node) // -r
		{
			ft_display_r(&(*node)->next, i);
			if (ft_strncmp((*node)->name, ".", 1))
				ft_putendl((*node)->name);
		}
}

void		ft_display_l_r(t_lst **node, int i)
{
	if (i)
	{
		if (*node)
		{
			ft_display_l_r(&(*node)->next, i);
			ft_display_data(node);
		}
	}
	else
		if (*node)
		{
			ft_display_l_r(&(*node)->next, i);
			if (ft_strncmp((*node)->name, ".", 1))
				ft_display_data(node);
		}
}

void		ft_display_t(t_lst **node)
{
	*node = ft_time_sort(*node);
	while (*node)
	{
		if (ft_strncmp((*node)->name, ".", 1) != 0)
			ft_putendl((*node)->name);
		*node = (*node)->next;
	}
}
