/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 15:14:01 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/19 17:43:25 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_init_opt(t_opt *opt)
{
	opt->l = 0;
	opt->R = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
}

int				ft_valid_opt(char c)
{
	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
		return (1);
	else
		return (0);
}

int				ft_check_opt(t_opt *opt)
{
	if (opt->l == 0 && opt->R == 0 && opt->a == 0 && opt->r == 0 && opt->t == 0)
		return (1);
	else
		return (0);
}

int				ft_options(char *s, t_opt *opt)
{
	int i;

	i = 1;
	while (s[i] && ft_valid_opt(s[i]))
	{
		if (s[i] == 'l')
			opt->l = 1;
		else if (s[i] == 'R')
			opt->R = 1;
		else if (s[i] == 'a')
			opt->a = 1;
		else if (s[i] == 'r')
			opt->r = 1;
		else if (s[i] == 't')
			opt->t = 1;
		i++;
	}
	if (s[i])
		ft_error_opt(&s[i]);
	return (0);
}

static void		ft_sort_options_bis(t_lst *node, t_opt *opt, char *path, int i)
{
	if (opt->l && (!opt->r))
	{
		if (node->next != NULL)
			ft_display_total(&node, i);
		ft_display_l(node, i);
	}
	else if (node && opt->a && (!opt->r))
		ft_display_curr(node, i);
	else if (node && (!opt->a) && (!opt->r))
		ft_display_curr(node, i);
	if (node && opt->R)
		ft_recursive(node, opt, path, ft_count_dir(node));
}

void			ft_sort_options(t_lst *node, t_opt *opt, char *path)
{
	int i;

	i = 0;
	node = ft_ascii_sort(node);
	if (!opt || ft_check_opt(opt))
		ft_display_curr(node, i);
	else
	{
		if (opt->a)
			i = 1;
		if (opt->t)
			node = ft_time_sort(node);
		if (opt->r && opt->l)
		{
			if (node->next != NULL)
				ft_display_total(&node, i);
			ft_display_l_r(&node, i);
		}
		else if (opt->r)
			ft_display_r(&node, i);
		ft_sort_options_bis(node, opt, path, i);
	}
}

void			ft_color_name(t_lst *node)
{
	if (node->file_data->get_perm[0] == 'd')
		ft_putstr(GREEN);
	else if (node->file_data->get_perm[0] == 'l')
		ft_putstr(RED);
	else if (node->file_data->get_perm[0] == 'c')
		ft_putstr(BLUE);
	else if (node->file_data->get_perm[0] == 'b')
		ft_putstr(MAGENTA);
	ft_putstr(node->name);
	ft_putstr(COLOR_RESET);
}
