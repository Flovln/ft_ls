/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 15:14:01 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/10 17:58:37 by fviolin          ###   ########.fr       */
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
		if (s[i] == 'R')
			opt->R = 1;
		if (s[i] == 'a')
			opt->a = 1;
		if (s[i] == 'r')
			opt->r = 1;
		if (s[i] == 't')
			opt->t = 1;
		i++;
	}
	return (0);
}

void			ft_sort_options(t_lst *node, t_opt *opt) //, char *path)
{
	int i;

	node = ft_ascii_sort(node);
	if (!opt || ft_check_opt(opt))  
		ft_display_curr(&node);
	else
	{
		if (opt->a) 
			i = 1;
		if (opt->t) // OK
			node = ft_time_sort(node);
		if (opt->r) // OK
			ft_display_r(&node, i);
		if (opt->l) // OK
			ft_display_l(&node);
	}
//	ft_display_curr(&node);
}
