/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 13:09:49 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/03 13:41:59 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_display_total(t_lst **node, int i)
{
	t_lst	*head;
	int		res;

	res = 0;
	head = *node;
	if (i)
		while (*node)
		{
			res += (*node)->file_data->blocks;
			*node = (*node)->next;
		}
	else
		while (*node)
		{
			if (ft_strncmp((*node)->name, ".", 1) != 0)
				res += (*node)->file_data->blocks;
			*node = (*node)->next;
		}
	ft_putstr("total ");
	ft_putnbr(res);
	ft_putchar('\n');
	*node = head;
}

void			ft_display_data(t_lst *node)
{
	ft_putstr_s(node->file_data->get_perm);
	ft_putstr_s(node->file_data->links);
	ft_putstr_s(node->file_data->uid);
	ft_putstr_s(node->file_data->gid);
	if (node->file_data->get_perm[0] != 'c' &&
			node->file_data->get_perm[0] != 'b')
	{
		ft_putstr("  ");
		ft_putstr(node->file_data->size);
		ft_putstr("  ");
	}
	else
		ft_putstr_s(node->file_data->maj_min);
	ft_putstr_s(node->date);
	ft_putstr(node->name);
	if (node->file_data->get_perm[0] == 'l')
		ft_put_link(node->path);
	ft_putchar('\n');
}

static	char	*ft_add_space(char *s, int max)
{
	int		i;
	int		j;
	int		k;
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
		ft_strdel(&tmp);
	return (s);
}

static void		ft_set_padding(t_lst **head, t_pad *pad)
{
	t_lst *tmp;

	tmp = *head;
	if (ft_count_node(tmp) > 1)
	{
		while (tmp)
		{
			tmp->file_data->links = ft_add_space(tmp->file_data->links,
					pad->links);
			tmp->file_data->uid = ft_strnjoin(tmp->file_data->uid, " ",
					(pad->uid - ft_strlen(tmp->file_data->uid)));
			tmp->file_data->gid = ft_strnjoin(tmp->file_data->gid, " ",
					(pad->gid - ft_strlen(tmp->file_data->gid)));
			tmp->file_data->size = ft_add_space(tmp->file_data->size,
					pad->size);
			tmp->file_data->min = ft_add_space(tmp->file_data->min, pad->min);
			tmp->file_data->maj = ft_add_space(tmp->file_data->maj, pad->maj);
			tmp->file_data->maj_min = ft_strjoin(tmp->file_data->maj, " ");
			tmp->file_data->maj_min = ft_strjoin(tmp->file_data->maj_min,
					tmp->file_data->min);
			tmp = tmp->next;
		}
	}
}

void			ft_padding(t_lst **head, t_pad *pad)
{
	t_lst	*tmp;

	tmp = *head;
	ft_init_pad(pad, head);
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
		if (pad->min < ft_strlen(tmp->next->file_data->min))
			pad->min = ft_strlen(tmp->next->file_data->min);
		if (pad->maj < ft_strlen(tmp->next->file_data->maj))
			pad->maj = ft_strlen(tmp->next->file_data->maj);
		tmp = tmp->next;
	}
	pad->maj_min = pad->min + pad->maj;
	ft_set_padding(head, pad);
}
