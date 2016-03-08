/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 16:48:01 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/08 17:19:56 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_get_lst(t_lst **node, DIR *dir, char *path)
{
	struct dirent *ret;

	while ((ret = readdir(dir)))
		*node = ft_get_data(*node, ret->d_name,
				ft_strjoin(path, ret->d_name));
	closedir(dir);
}

static void		ft_read_bis(t_lst *node, char *path, t_pad *pad, t_opt *opt)
{
	if (opt && opt->l) //Segfault with padding w/ -Rr + -Rlr /library ~/
		ft_padding(&node, pad);
	ft_sort_options(node, opt, path);
	if (!opt->maj_r && !node->next)
		ft_free_list(&node);
	else if (!opt->maj_r && node)
		ft_free_list(&node);
	free(pad);
	pad = NULL;
}

void			ft_read_param(char *path, t_opt *options)
{
	DIR		*dir;
	t_lst	*node;
	t_pad	*pad;
	int		is_file;

	is_file = 0;
	pad = (t_pad *)malloc(sizeof(t_pad));
	if (!(node = (t_lst *)malloc(sizeof(t_lst))))
		exit(1);
	node = NULL;
	if (!(dir = opendir(path)))
	{
		node = manage_av_file(path, node, dir);
		if (!node && ft_error(path))
			return ;
		else if (ft_error_rights(node, path))
			return ;
		is_file = 1;
	}
	else if (is_file == 0)
	{
		path = ft_add_slash(path);
		ft_get_lst(&node, dir, path);
	}
	ft_read_bis(node, path, pad, options);
}
