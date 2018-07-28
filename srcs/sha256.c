/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 16:03:15 by gwood             #+#    #+#             */
/*   Updated: 2018/07/27 13:26:55 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

static t_sha256 *init(void)
{
    t_sha256 *ret;

    ret = (t_sha256 *)ft_memalloc(sizeof(t_sha256));
    ret->h0 =   0x6a09e667;
    ret->h1 =   0xbb67ae85;
    ret->h2 =   0x3c6ef372;
    ret->h3 =   0xa54ff53a;
    ret->h4 =   0x510e527f;
    ret->h5 =   0x9b05688c;
    ret->h6 =   0x1f83d9ab;
    ret->h7 =   0x5be0cd19;
    ret->offset = 0;
    ret->msg = NULL;
    ret->msgsched = NULL;
    return (ret);
}

static void	    padding(t_sha256 *d, char *message)
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

static void op_loop(t_sha256 *d, uint32_t i)
{
    uint32_t    tmp1;
    uint32_t    tmp2;

    tmp1 = d->h + BSIG1(d->e) + CH(d->e, d->f, d->g) + g_s256[i] + d->msgsched[i];
    tmp2 = BSIG0(d->a) + MAJ(d->a, d->b, d->c);
    d->h = d->g;
    d->g = d->f;
    d->f = d->e;
    d->e = d->d + tmp1;
    d->d = d->c;
    d->c = d->b;
    d->b = d->a;
    d->a = tmp1 + tmp2;
}

static void     chunk_loop(t_sha256 *d)
{
    uint32_t    i;

    d->offset += 512 / 8;
    d->msgsched = (uint32_t *)ft_memalloc(sizeof(uint32_t) * 64);
    // ft_memcpy(d->msgsched, d->words, sizeof(uint32_t) * 16);
    i = 0;
    while (i < 16)
    {
        d->msgsched[i] = ft_bswap32(d->msg[i + d->offset]);
        i += 4;
    }
    while (++i < 64)
        d->msgsched[i] = d->msgsched[i - 16] + SSIG0(d->msgsched[i - 15]) +
            d->msgsched[i - 7] + SSIG1(d->msgsched[i - 2]);
    d->a = d->h0;
    d->b = d->h1;
    d->c = d->h2;
    d->d = d->h3;
    d->e = d->h4;
    d->f = d->h5;
    d->g = d->h6;
    d->h = d->h7;
    i = -1;
    while (++i < 64)
        op_loop(d, i);
    d->h0 += d->a;
    d->h1 += d->b;
    d->h2 += d->c;
    d->h3 += d->d;
    d->h4 += d->e;
    d->h5 += d->f;
    d->h6 += d->g;
    d->h7 += d->h;
}

char		    *ft_sha256(char *message)
{
    t_sha256 *d;
    char        *digest;

    digest = NULL;
    d = init();
	d->length = ft_strlen(message);
    padding(d, message);
	while (d->offset < d->length)
        chunk_loop(d);
    digest = ft_uitoa_base(ft_bswap32(d->h0), 16);
	digest = ft_strcat(digest, ft_uitoa_base(ft_bswap32(d->h1), 16));
	digest = ft_strcat(digest, ft_uitoa_base(ft_bswap32(d->h2), 16));
	digest = ft_strcat(digest, ft_uitoa_base(ft_bswap32(d->h3), 16));
	digest = ft_strcat(digest, ft_uitoa_base(ft_bswap32(d->h4), 16));
	digest = ft_strcat(digest, ft_uitoa_base(ft_bswap32(d->h5), 16));
	digest = ft_strcat(digest, ft_uitoa_base(ft_bswap32(d->h6), 16));
	digest = ft_strcat(digest, ft_uitoa_base(ft_bswap32(d->h7), 16));
    free(d);
	return (digest);
}
