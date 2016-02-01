/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:14:08 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/01 17:12:50 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

static void		ft_add_data(struct stat file_stat, t_lst *node, char *file) // char *path)
{
	struct passwd	*user_name;
	struct group	*group_name;

	if ((user_name = getpwuid(file_stat.st_uid)))
		node->file_data->uid = ft_strdup(user_name->pw_name);
	if ((group_name = getgrgid(file_stat.st_gid)))
		node->file_data->gid = ft_strdup(group_name->gr_name);
	node->name = file;
	node->date = ft_strsub(ctime(&file_stat.st_mtime), 4, 12);
	node->file_data->links = ft_itoa(file_stat.st_nlink);
	node->file_data->size = ft_itoa(file_stat.st_size);
	ft_perm_acc(node, &file_stat);
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
