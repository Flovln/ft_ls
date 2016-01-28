/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:11:19 by fviolin           #+#    #+#             */
/*   Updated: 2016/01/28 16:24:29 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


t_lst_info		*create_lst()
{
	t_lst_info *new_node;

	new_node = (t_lst_info *)malloc(sizeof(t_lst_info));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	return (new_node);
}

void		add_node(t_lst_info **head, t_lst_info *new)
{
	t_lst_info *tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void			add_data_tonode(t_lst_info *new_node, struct stat file_stat)
{
		struct passwd	*user_name;
		struct group	*group_name;
		char			*date_cut;

		user_name = getpwuid(file_stat.st_uid);
		new_node->uid = user_name;

		group_name = getgrgrid(file_stat.st_gid);
		new_node->gid = group_name;

		new_node->size = file_stat.st_size;

		date = ctime(&file_stat.st_mtime);
		date_cut = ft_strsub(date, 4, 12);
		new_node->date = date_cut;
}

void			free_lst(t_lst_info **head)
{
	t_lst_info	*tmp;
	t_lst_info	*next;

	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		ft_free_data(tmp->data); //free le contenu de la node
		tmp->data = NULL;
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}
