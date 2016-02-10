/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 17:59:52 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/10 18:05:06 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_display_total(t_lst **node)
{
	t_lst   *head;

	head = *node;
	while (*node)
	{
		if ((*node)->next == NULL)
		{
			ft_putstr("total ");
			ft_putstr((*node)->file_data->blocks);
			ft_putstr("\n");
		}
		*node = (*node)->next;
	}
	*node = head;
}

void        ft_display_curr(t_lst **node) // ls command
{
	while (*node)
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
	{
		while (*node)
		{
			ft_putstr((*node)->file_data->get_perm);
			ft_putstr("  ");
			ft_putstr((*node)->file_data->links);
			ft_putstr(" ");
			ft_putstr((*node)->file_data->uid);
			ft_putstr("  ");
			ft_putstr((*node)->file_data->gid);
			ft_putstr(" ");
			ft_putstr((*node)->file_data->size);
			ft_putstr("  ");
			ft_putstr((*node)->date);
			ft_putstr(" ");
			ft_putendl((*node)->name);
			*node = (*node)->next;
		}
	}
	else // -l
		ft_display_data(node);
}

void        ft_display_r(t_lst **node, int i) // ls -r command
{
	if (i == 1) //display all for '-a'
	{
		if (*node)
		{
			ft_display_r(&(*node)->next, i);
			ft_putendl((*node)->name);
		}
	}
	else
	{
		if (*node) // doesn't display hidden files
		{
			ft_display_r(&(*node)->next, i);
			if (ft_strncmp((*node)->name, ".", 1))
				ft_putendl((*node)->name);
		}
	}
}
