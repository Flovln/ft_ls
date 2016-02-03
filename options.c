/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 15:14:01 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/03 16:09:37 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_init_opt(t_opt *opt)
{
	opt->l = 0;
	opt->R = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
}
/*
static void	print_opt(t_opt *opt) // test
{
	ft_putendl("--- OPT SAVED ---\n");
	printf("l is -> %d\n", opt->l);
	printf("R is -> %d\n", opt->R);
	printf("a is -> %d\n", opt->a);
	printf("r is -> %d\n", opt->r);
	printf("t is -> %d\n\n", opt->t);
}
*/
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
	ft_init_opt(opt);
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
