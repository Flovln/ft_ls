/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 15:14:01 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/10 13:06:40 by fviolin          ###   ########.fr       */
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

int				ft_valid_options(char c)
{
	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
		return (1);
	else
		return (0);
}

int				ft_options(char *s, t_opt *opt)
{
	int i;

	i = 1;
	while (s[i] && ft_valid_options(s[i]))
	{
		if (s[i] == 'l')
			opt->l = 1;
		if (s[i] == 'R')
			opt->R = 1;
		if (s[i] == 'a')
			opt->a = 1;
		if (s[i] == 'r')
			opt->r = 1;
		if (s[i] == 't')
			opt->r = 1;
		i++;
	}
	//	print_opt(opt);
	return (0);
}

void			ft_sort_options(t_lst *node, t_opt *opt) //, char *path)
{
	node = ft_ascii_sort(node);
	if (!opt)
	{
		ft_display_curr(&node);
		return ;
	}
	if (opt->l == 0 && opt->R == 0 && opt->a == 0 && opt->r == 0 && opt->t == 0)
		ft_display_curr(&node);
	if (node != NULL && opt->l)
		ft_display_l(&node);
	else if (opt->t)
		node = ft_time_sort(node);
}

