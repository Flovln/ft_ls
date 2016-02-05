/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:14:08 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/05 13:51:12 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/////void			ft_free_list(t_lst *head)
/*
static void		ft_new_node_head(t_lst **head, t_lst *new_node)
{
	if (!*head)
		*head = new_node;
	else
	{
		new_node->next = *head;
		*head = new_node;
	}
}

void		ft_add_node(t_lst **head, t_lst *current, t_lst *new_node)
{
	if (!*head)
		*head = new_node;
	while ((*head)->next)
		*head = (*head)->next;
	(*head)->next = new_node;
//	printf("HEAD in new_node is %s\n", (*head)->name);
}
*/

t_lst		*ft_get_data(t_lst *head, char *file, char *path)
{
	struct stat file_st;
	t_lst		*tmp;
	t_lst		*current;

	tmp = (t_lst *)malloc(sizeof(t_lst));
	tmp->file_data = (t_data *)malloc(sizeof(t_data)); //pour structure t_data appelee dans struct t_lst
	current = head;
	if (lstat(path, &file_st) <= 0)
		ft_add_data(file_st, tmp, file); //, path);
//	printf("TMP is %s\n", tmp->name);
	if (head == NULL)
		return (tmp);
	while (current->next != NULL)
		current = current->next;
	current->next = tmp;
//	ft_add_node(&head, current, tmp);
	return (head);
}
