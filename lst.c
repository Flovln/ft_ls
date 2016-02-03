/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:14:08 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/03 10:56:29 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/////void			ft_free_list(t_lst *head)
/*
void		ft_sort_lst(t_lst *head)
{
	t_lst 	*tmp;
	char	*swap;

	tmp = head;
	while (head->next)
	{
		if ((ft_strcmp(head->next->name, head->name) < 0))
		{
			swap = head->name;
			head->name = head->next->name;
			head->next->name = swap;
			head = tmp;
		}
		else
			head = head->next;
	}
	head = tmp;
}
*/
static void		ft_new_node(t_lst *head, t_lst *new_node)
{
	if (!head) // == NULL
	{
		head = new_node;
		return ;
	}
	while (head->next)
		head = head->next;
	head->next = new_node;
}

t_lst			*ft_get_data(t_lst *head, char *file, char *path)
{
	struct stat file_st;
	t_lst		*tmp;

	tmp = (t_lst *)malloc(sizeof(t_lst));
	tmp->file_data = (t_data *)malloc(sizeof(t_data)); //pour structure t_data appelee dans struct t_lst
	tmp->next = NULL;
	if (stat(path, &file_st) == 1)
	{
		ft_putendl("ft_get_data failed");
		exit(EXIT_FAILURE);
	}
	if (lstat(path, &file_st) <= 0)
		ft_add_data(file_st, tmp, file); //, path);
	ft_new_node(head, tmp);
	return (tmp);
}
