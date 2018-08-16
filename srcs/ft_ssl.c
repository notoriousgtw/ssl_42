/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 21:12:33 by gwood             #+#    #+#             */
/*   Updated: 2018/08/15 17:33:38 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"


static t_ft_ssl_data	*init(char *ssl_cmd)
{
	int				i;
	t_ft_ssl_data	*ret;

	if (!(ret = (t_ft_ssl_data *)ft_memalloc(sizeof(t_ft_ssl_data))))
		return (NULL);
	ret->ssl_prg = NULL;
	i = 0;
	while (g_ft_ssl_program_list[i].name != NULL)
	{
		if (!(ft_strcmp(g_ft_ssl_program_list[i].name, ssl_cmd)))
			ret->ssl_prg = &(((t_ft_ssl_prg *)g_ft_ssl_program_list)[i]);
		i++;
	}
	if (ret->ssl_prg == NULL)
		ft_ssl_error_invalid_command(ssl_cmd);
	return (ret);
}

int						main(int argc, char **argv)
{
	t_ft_ssl_data	*d;

	if (argc > 1 && argv[1] != NULL)
	{
		d = init(argv[1]);
		d->ssl_prg->ssl_fnc(argc - 1, argv + 1);
	}
	else
		ft_putendl("usage: ft_ssl command [command opts] [command args]");
}
