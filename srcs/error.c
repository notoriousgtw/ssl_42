/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 12:42:21 by gwood             #+#    #+#             */
/*   Updated: 2018/08/09 18:26:22 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"

void    ft_ssl_error_prg(t_ft_ssl_data *d, char *prg)
{
    const t_ft_ssl_prg *iter;

    ft_putstr_fd("ft_ssl: Error: ", 2);
    ft_putstr_fd(prg, 2);
    ft_putstr_fd(" is an invlaid command.\n\nValid comands are:\n\n", 2);
    iter = g_ft_ssl_program_list;
    while(iter->name != NULL)
        ft_putendl_fd((iter++)->name, 2);
    ft_error_free(NULL, (t_free_fnc)ft_ssl_free_data, d);
}

void    ft_ssl_error_nostring(t_ft_ssl_data *d)
{
    ft_putstr_fd("ft_ssl: ", 2);
    ft_putstr_fd(d->ssl_prg->name, 2);
    ft_error_free(": Error: -s argument present but no string provided",
        (t_free_fnc)ft_ssl_free_data, d);
}
