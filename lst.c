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

void			ft_add_node(t_lst_info *head, t_lst_info *new_node)
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

static void		ft_add_data(struct stat file_stat, t_lst_info *node, char *file, char *path)
{
	struct passwd	*user_name;
	struct group	*group_name;

	if ((user_name = getpwuid(file_stat.st_uid)))
		node->uid = user_name->pw_name;
	if ((group_name = getgrgid(file_stat.st_gid)))
		node->gid = group_name->gr_name;
	node->name = file;
	node->chem = path;
}

t_lst_info		*ft_get_data(t_lst_info *head, char *file, char *path)
{
	struct stat file_st;
	t_lst_info	*tmp;

	tmp = (t_lst_info *)malloc(sizeof(t_lst_info));
	tmp->next = NULL;
	if (lstat(path, &file_st) <= 0)
		ft_add_data(file_st, tmp, file, path);
	ft_add_node(head, tmp);
	return (tmp);
}
