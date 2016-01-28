/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:11:19 by fviolin           #+#    #+#             */
/*   Updated: 2016/01/28 18:27:52 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_lst_info		*ft_create_lst(struct dirent *ret, struct stat *file_stat)
{
	t_lst_info *new_node;

	new_node = (t_lst_info *)malloc(sizeof(t_lst_info));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	return (new_node);
}

void		ft_new_node(t_lst_info **head, t_lst_info *new_node)
{
	t_lst_info *tmp;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void			ft_add_data(t_lst_info *new_node, struct stat *file_stat)
{
		struct passwd	*user_name;
		struct group	*group_name;
		char			*date;
		char			*date_cut;

		ft_get_rights(new_node, file_stat); //permission access
		new_node->file_data->link = ft_itoa(file_stat->st_nlink); // nb fichiers/dossier + sous dossiers
		user_name = getpwuid(file_stat->st_uid); // owner name
		new_node->file_data->uid = user_name; // 
		group_name = getgrgrid(file_stat->st_gid); // group name
		new_node->file_data->gid = group_name; //
		new_node->file_data->size = ft_itoa(file_stat->st_size); // taille fichier/dossier
		date = ctime(&file_stat->st_mtime); // date, heure
		date_cut = ft_strsub(date, 4, 12); //
		new_node->file_data->date = date_cut; //
}

void			ft_free_lst(t_lst_info **head)
{
	t_lst_info	*tmp;
	t_lst_info	*next;

	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
//		free_data(tmp->data); //free le contenu de la node
//		tmp->data = NULL;
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}
