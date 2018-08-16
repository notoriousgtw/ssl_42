/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 21:12:33 by gwood             #+#    #+#             */
/*   Updated: 2018/08/16 13:19:09 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"

int						main(int argc, char **argv)
{
	int				i;
	t_ft_ssl_prg	*ssl_prg;

	if (argc > 1 && argv[1] != NULL)
	{
		ssl_prg = NULL;
		i = 0;
		while (g_ft_ssl_program_list[i].name != NULL)
		{
			if (!(ft_strcmp(g_ft_ssl_program_list[i].name, argv[1])))
				ssl_prg = &(((t_ft_ssl_prg *)g_ft_ssl_program_list)[i]);
			i++;
		}
		if (ssl_prg == NULL)
			ft_ssl_error_invalid_command(argv[1]);
		ssl_prg->ssl_fnc(argc - 1, argv + 1);
	}
	else
		ft_putendl("usage: ft_ssl command [command opts] [command args]");
}
