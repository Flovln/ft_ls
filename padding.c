/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 13:09:49 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/02 14:33:55 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_init_pad(t_pad *pad)
{
	pad->links = 0;
	pad->uid = 0;
	pad->gid = 0;
	pad->size = 0;
}

static	char	*ft_add_space(char *s, int max)
{
	int 	i;
	int 	j;
	int 	k;
	char	*tmp;

	i = 0;
	j = max - (int)ft_strlen(s);
	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (NULL);
	if (j > 0)
	{
		while (i < max)
		{
			while (i < j)
				tmp[i++] = ' ';
			k = 0;
			while (i < max)
				tmp[i++] = s[k++];
			i++;
		}
		return (tmp);
	}
	else
		return (s);
}

static void		apply_padding(t_lst *head, t_pad *pad)
{
	t_lst *tmp;

	tmp = head;
	ft_init_pad(pad);
	while (head->next)
	{
		tmp = tmp->next;
		tmp->file_data->links = ft_add_space(tmp->file_data->links, pad->links);
		tmp->file_data->uid = ft_add_space(tmp->file_data->uid, pad->uid);
		tmp->file_data->gid = ft_add_space(tmp->file_data->uid, pad->gid);
		tmp->file_data->size = ft_add_space(tmp->file_data->size, pad->size);
	}
	tmp->next = NULL;
}

void			padding(t_lst *head, t_pad *pad)
{
	t_lst	*tmp;
//	t_pad	*pad;

	tmp = head;
	pad = (t_pad *)malloc(sizeof(t_pad));
	pad = NULL;
	ft_init_pad(pad);
	while (tmp->next)
	{
		if (pad->links < ft_strlen(tmp->next->file_data->links))
			pad->links = ft_strlen(tmp->next->file_data->links);
		if (pad->uid < ft_strlen(tmp->next->file_data->uid))
			pad->uid = ft_strlen(tmp->next->file_data->uid);
		if (pad->gid < ft_strlen(tmp->next->file_data->gid))
			pad->gid = ft_strlen(tmp->next->file_data->gid);
		if (pad->size < ft_strlen(tmp->next->file_data->size))
			pad->size = ft_strlen(tmp->next->file_data->size);
		tmp = tmp->next;
	}
	apply_padding(head, pad);
}
