/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:14:08 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/03 14:23:18 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/////void			ft_free_list(t_lst *head)
//if ((ft_strcmp(head->name, head->next->name) < 0))

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
