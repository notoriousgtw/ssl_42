/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 12:42:21 by gwood             #+#    #+#             */
/*   Updated: 2018/08/15 16:27:46 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_ssl_error_invalid_command(char *cmd)
{
	const t_ft_ssl_prg *iter;

	ft_putstr_fd("ft_ssl: Error: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" is an invlaid command.\n\nValid comands are:\n\n", 2);
	iter = g_ft_ssl_program_list;
	while (iter->name != NULL)
		ft_putendl_fd((iter++)->name, 2);
	ft_error(NULL);
}
