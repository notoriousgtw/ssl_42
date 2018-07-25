/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 21:12:33 by gwood             #+#    #+#             */
/*   Updated: 2018/07/24 18:58:09 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "md5.h"

void		display_usage(char *name)
{
    ft_putstr("usage: ");
    ft_putstr(name);
    ft_putendl(" message");
}


int			main(int argc, char *argv[])
{
	if (argc == 2)
	{
		ft_putstr(ft_md5(argv[1]));
		// ft_md5(argv[1]);
	}
	else
		display_usage(*argv);
	return (0);
}
