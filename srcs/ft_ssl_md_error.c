/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 12:42:21 by gwood             #+#    #+#             */
/*   Updated: 2018/08/15 16:40:51 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md.h"

void	ft_ssl_md_error_no_string(t_ft_ssl_md_data *d)
{
	ft_putstr_fd("ft_ssl: ", 2);
	ft_putstr_fd(d->name, 2);
	ft_error_free(": Error: -s argument present but no string provided",
		(t_free_fnc)ft_ssl_md_free_data, d);
}

void	ft_ssl_md_error_invalid_file(t_ft_ssl_md_data *d, char *filename)
{
	ft_putstr_fd("ft_ssl: ", 2);
	ft_putstr_fd(d->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(filename, 2);
	ft_putendl_fd(": No such file", 2);
}
