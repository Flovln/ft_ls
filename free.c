/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 17:01:52 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/03 14:01:55 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
}

void	ft_free_data(t_lst **node)
{
	if ((*node)->file_data->links)
		ft_strdel(&(*node)->file_data->links);
	if ((*node)->file_data->uid)
		ft_strdel(&(*node)->file_data->uid);
	if ((*node)->file_data->gid)
		ft_strdel(&(*node)->file_data->gid);
	if ((*node)->file_data->min)
		ft_strdel(&(*node)->file_data->min);
	if ((*node)->file_data->maj)
		ft_strdel(&(*node)->file_data->maj);
	if ((*node)->file_data->size)
		ft_strdel(&(*node)->file_data->size);
	else
		ft_strdel(&(*node)->file_data->maj_min);
	if ((*node)->date)
		ft_strdel(&(*node)->date);
	if ((*node)->name)
		ft_strdel(&(*node)->name);
//	if ((*node)->path)
//		ft_strdel(&(*node)->path);
}

void	ft_free_list(t_lst **node)
{
	while (*node)
	{
		ft_free_data(node);
		*node = (*node)->next;
	}
	free((*node));
	node = NULL;
}
