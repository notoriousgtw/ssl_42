/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 16:03:15 by gwood             #+#    #+#             */
/*   Updated: 2018/08/13 10:53:24 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include "bswap_utils.h"

static t_sha256 *init(void)
{
    t_sha256 *ret;

    ret = (t_sha256 *)ft_memalloc(sizeof(t_sha256));
    ret->h0 = 0x6a09e667;
    ret->h1 = 0xbb67ae85;
    ret->h2 = 0x3c6ef372;
    ret->h3 = 0xa54ff53a;
    ret->h4 = 0x510e527f;
    ret->h5 = 0x9b05688c;
    ret->h6 = 0x1f83d9ab;
    ret->h7 = 0x5be0cd19;
    ret->msg = NULL;
    ret->msgsched = NULL;
    return (ret);
}

static void	    padding(t_sha256 *d, t_byte *message)
{

    uint32_t    i;
	size_t		new_length;
    uint32_t	bit_length;



    new_length = d->length * 8 + 1;
    while (new_length % 512 != 448)
    	new_length++;
    new_length /= 8;
    d->msg = (uint32_t *)ft_memalloc(new_length + 64);
    ft_memcpy(d->msg, message, d->length);
    ((uint8_t *)d->msg)[d->length] = 128;
    i = 0;
    while (i < d->length)
        ft_bswap32_v(d->msg + i++);
    bit_length = (uint32_t)8 * d->length;
    ft_memcpy(((uint8_t *)d->msg) + new_length + 4, &bit_length, 4);
	d->length = new_length + 8;
}

static void op_loop(t_sha256 *d, uint32_t i)
{
    uint32_t    tmp1;
    uint32_t    tmp2;

    tmp1 = d->h + BSIG1(d->e) + CH(d->e, d->f, d->g) + g_k_s256[i] +
        d->msgsched[i];
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

static void     chunk_loop(t_sha256 *d, uint32_t i)
{
    uint32_t    j;

    d->msgsched = (uint32_t *)ft_memalloc(sizeof(uint32_t) * 64);
    ft_memcpy(d->msgsched, d->msg + i * 16, sizeof(uint32_t) * 16);
    j = 16;
    while (j < 64)
    {
        d->msgsched[j] = d->msgsched[j - 16] +
            SSIG0(d->msgsched[j - 15]) + d->msgsched[j - 7] +
            SSIG1(d->msgsched[j - 2]);
        j++;
    }
    d->a = d->h0;
    d->b = d->h1;
    d->c = d->h2;
    d->d = d->h3;
    d->e = d->h4;
    d->f = d->h5;
    d->g = d->h6;
    d->h = d->h7;
    j = 0;
    while (j < 64)
        op_loop(d, j++);
    d->h0 += d->a;
    d->h1 += d->b;
    d->h2 += d->c;
    d->h3 += d->d;
    d->h4 += d->e;
    d->h5 += d->f;
    d->h6 += d->g;
    d->h7 += d->h;
    free(d->msgsched);
}

char		    *ft_sha256(t_byte *message, size_t length)
{
    uint32_t    i;
    t_sha256    *d;
    char        *digest;

    d = init();
	d->length = length;
    padding(d, message);
    i = 0;
	while (i < d->length / 64)
        chunk_loop(d, i++);
    digest = ft_strnew(64);
	digest = ft_strjoinfree(digest, ft_uitoa(d->h0, 16), 3);
	digest = ft_strjoinfree(digest, ft_uitoa(d->h1, 16), 3);
	digest = ft_strjoinfree(digest, ft_uitoa(d->h2, 16), 3);
	digest = ft_strjoinfree(digest, ft_uitoa(d->h3, 16), 3);
	digest = ft_strjoinfree(digest, ft_uitoa(d->h4, 16), 3);
	digest = ft_strjoinfree(digest, ft_uitoa(d->h5, 16), 3);
	digest = ft_strjoinfree(digest, ft_uitoa(d->h6, 16), 3);
	digest = ft_strjoinfree(digest, ft_uitoa(d->h7, 16), 3);
    digest[64] = 0;
    free(d->msg);
    free(d);
	return (digest);
}
