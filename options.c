/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 15:14:01 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/10 14:03:01 by fviolin          ###   ########.fr       */
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
/*
static int		ft_check_opt(char c)
{
	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
		return (1);
	else
		return (0);
}
*/
int				ft_valid_opt(t_opt *opt)
{
	if (opt->l == 0 && opt->R == 0 && opt->a == 0 && opt->r == 0 && opt->t == 0)
		return (1);
	else
		return (0);
}

int				ft_options(char *s, t_opt *opt)
{
//	int i;

//	i = 1;
	while (*s) // && ft_check_opt(*s))
	{
		if (*s == 'l')
			opt->l = 1;
		if (*s == 'R')
			opt->R = 1;
		if (*s == 'a')
			opt->a = 1;
		if (*s == 'r')
			opt->r = 1;
		if (*s == 't')
			opt->r = 1;
		s++;
	}
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
	if (ft_valid_opt(opt)) // != 0 >> == 1
		ft_display_curr(&node);
	if (node != NULL && opt->l)
		ft_display_l(&node);
	else if (opt->t)
		node = ft_time_sort(node);
}

