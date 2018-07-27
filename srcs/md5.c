/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 16:03:15 by gwood             #+#    #+#             */
/*   Updated: 2018/07/24 20:28:28 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"


const uint32_t g_k[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee ,
                        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 ,
                        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,
                        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 ,
                        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa ,
                        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 ,
                        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed ,
                        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a ,
                        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c ,
                        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 ,
                        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 ,
                        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 ,
                        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 ,
                        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 ,
                        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 ,
                        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

const uint32_t g_s[] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static t_md5	*init(void)
{
    t_md5 *ret;

    ret = (t_md5 *)ft_memalloc(sizeof(t_md5));
    ret->h0 = 0x67452301;
    ret->h1 = 0xefcdab89;
    ret->h2 = 0x98badcfe;
    ret->h3 = 0x10325476;
    ret->msg = NULL;
    ret->offset = 0;
    return (ret);
}

static void	    padding(t_md5 *d, char *message)
{
	size_t		new_length;
    uint64_t	bit_length;

    new_length = d->length * 8 + 1;
    while (new_length % 512 != 448)
	{
    	new_length++;
	}
    new_length /= 8;
    d->msg = (uint8_t *)ft_memalloc(new_length + 64);
    ft_memcpy(d->msg, message, d->length);
    d->msg[d->length] = 128;
    bit_length = (uint64_t)8 * d->length;
    ft_memcpy(d->msg + new_length, &bit_length, 8);
	d->length = new_length + 8;
}

static void op(t_md5 *d, uint32_t i)
{
    uint32_t    f;
    uint32_t    g;
	uint32_t	tmp;

    if (i < 16) {
        f = (d->b & d->c) | ((~(d->b)) & d->d);
        g = i;
    } else if (i < 32) {
        f = (d->d & d->b) | ((~(d->d)) & d->c);
        g = (5*i + 1) % 16;
    } else if (i < 48) {
        f = d->b ^ d->c ^ d->d;
        g = (3*i + 5) % 16;
    } else {
        f = d->c ^ (d->b | (~(d->d)));
        g = (7*i) % 16;
    }
    tmp = d->d;
    d->d = d->c;
    d->c = d->b;
    d->b = d->b + LEFTROTATE((d->a + f + g_k[i] + d->words[g]), g_s[i]);
    d->a = tmp;
}

static void     word_loop(t_md5 *d)
{
    uint32_t    i;

    d->words = (uint32_t *) (d->msg + d->offset);
    d->offset += 512 / 8;
    d->a = d->h0;
    d->b = d->h1;
    d->c = d->h2;
    d->d = d->h3;
    i = -1;
    while (++i < 64)
        op(d, i);
    d->h0 += d->a;
    d->h1 += d->b;
    d->h2 += d->c;
    d->h3 += d->d;
}

char		    *ft_md5(char *message)
{
    t_md5 *d;
    char        *digest;

    digest = NULL;
    d = init();
	d->length = ft_strlen(message);
    padding(d, message);
	while (d->offset < d->length)
        word_loop(d);
    digest = ft_uitoa_base(ft_bswap32(d->h0), 16);
	digest = ft_strcat(digest, ft_uitoa_base(ft_bswap32(d->h1), 16));
	digest = ft_strcat(digest, ft_uitoa_base(ft_bswap32(d->h2), 16));
	digest = ft_strcat(digest, ft_uitoa_base(ft_bswap32(d->h3), 16));
    free(d);
	return (digest);
}
