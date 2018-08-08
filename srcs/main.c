/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 21:12:33 by gwood             #+#    #+#             */
/*   Updated: 2018/08/07 12:30:53 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include "stdio.h"

int	main(int argc, char **argv)
{
	char *digest;

	digest = ssl_parser(argc, argv);
	printf("\n\ndigest: %s\n", digest);
	return (0);
}
