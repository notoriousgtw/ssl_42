/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 16:00:06 by gwood             #+#    #+#             */
/*   Updated: 2018/07/24 19:04:00 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "libft.h"
# include <inttypes.h>

# define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

typedef struct  s_md5
{
	size_t		length;
	uint8_t		*msg;
    uint32_t    h0;
    uint32_t    h1;
    uint32_t    h2;
    uint32_t    h3;
	uint32_t 	a;
	uint32_t 	b;
	uint32_t 	c;
	uint32_t 	d;
	uint32_t 	offset;
	uint32_t 	*words;
}               t_md5;

char		    *ft_md5(char *message);
#endif
