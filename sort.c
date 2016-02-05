/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 13:25:15 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/05 13:47:41 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	t_lst	*ft_lst_swap(t_lst *node, t_lst *node_next)
{
	node->next = node_next->next;
	node_next->next = node;
	return (node_next);
}

t_lst			*ft_ascii_sort(t_lst *node)
{
	if (!node)
		return (NULL);
	if (node->next != NULL && ft_strcmp(node->name, node->next->name) > 0)
		node = ft_lst_swap(node, node->next);
	node->next = ft_ascii_sort(node->next);
	if (node->next != NULL && ft_strcmp(node->name, node->next->name) > 0)
	{
		node = ft_lst_swap(node, node->next);
		node->next = ft_ascii_sort(node->next);
	}
	return (node);
}
