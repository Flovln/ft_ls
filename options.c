/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 15:14:01 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/11 20:11:58 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_valid_opt(char c)
{
	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
		return (1);
	else
		return (0);
}

int				ft_check_opt(t_opt *opt)
{
	if (opt->l == 0 && opt->maj_r == 0 && opt->a == 0
			&& opt->r == 0 && opt->t == 0)
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
			opt->maj_r = 1;
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
	if (node && opt->maj_r)
		ft_recursive(node, opt, path);
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
			ft_display_l_r(node, i);
		}
		else if (opt->r)
			ft_display_r(node, i);
		ft_sort_options_bis(node, opt, path, i);
	}
}
