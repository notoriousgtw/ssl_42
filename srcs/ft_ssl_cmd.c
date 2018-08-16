/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 16:06:57 by gwood             #+#    #+#             */
/*   Updated: 2018/08/16 12:58:58 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md.h"

void	ft_ssl_md5(int argc, char **argv)
{
	ft_ssl_md(argc, argv, &ft_md5);
}

void	ft_ssl_sha256(int argc, char **argv)
{
	ft_ssl_md(argc, argv, &ft_sha256);
}

void	ft_ssl_sha224(int argc, char **argv)
{
	ft_ssl_md(argc, argv, &ft_sha224);
}

void	ft_ssl_sha512(int argc, char **argv)
{
	ft_ssl_md(argc, argv, &ft_sha512);
}

void	ft_ssl_sha384(int argc, char **argv)
{
	ft_ssl_md(argc, argv, &ft_sha384);
}
