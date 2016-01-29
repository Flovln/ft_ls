/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:14:08 by fviolin           #+#    #+#             */
/*   Updated: 2016/01/29 17:55:20 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_new_node(t_lst_info **head, t_lst_info *new_node)
{
	t_lst_info	*current;

	if (!*head) // == NULL
	{
		*head = new_node;
		return ;
	}
	else
		current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

static void		ft_add_data(struct stat *file_stat, t_lst_info *node, char *file, char *path)
{
	struct passwd	*user_name;
	struct group	*group_name;

	if ((user_name = getpwuid(file_stat->st_uid)))
		node->uid = user_name->pw_name;
	if ((group_name = getgrgid(file_stat->st_gid)))
		node->gid = group_name->gr_name;
	node->name = file;
}

t_lst_info		*ft_get_data(t_lst_info *head, char *path, char *file)
{
	struct stat file_stat;
	t_lst_info	*node_data;

	node_data = (t_lst_info *)malloc(sizeof(t_lst_info));
	node_data->next = NULL;
	if (stat(path, &file_stat) == 1)
	{	
		ft_putendl("fail to get stats");
		exit(EXIT_FAILURE);
	}
	if (lstat(path, &file_stat) <= 0)
		ft_add_data(&file_stat, node_data, file, path);
	ft_new_node(&head, node_data);
	return (node_data);
}
