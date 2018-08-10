/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 16:03:15 by gwood             #+#    #+#             */
/*   Updated: 2018/08/09 15:14:54 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include "bswap_utils.h"
#include <stdio.h>

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
    ret->msg = NULL;
    ret->msgsched = NULL;
    return (ret);
}

static void	    padding(t_sha256 *d, t_byte *message)
{
    // uint64_t    n = 435475931745;
    uint32_t    i;
	size_t		new_length;
    uint32_t	bit_length;

    // message++;
    // d->length = 5;
    new_length = d->length * 8 + 1;
    while (new_length % 512 != 448)
	{
    	new_length++;
	}
    new_length /= 8;
    d->msg = (uint32_t *)ft_memalloc(new_length + 64);
    ft_memcpy(d->msg, message, d->length);
    ((uint8_t *)d->msg)[d->length] = 128;
    // d->msg = ft_bswap_array(d->msg, d->length, sizeof(uint32_t));
    i = 0;
    while (i < d->length)
        ft_bswap32_v(d->msg + i++);
    bit_length = (uint32_t)8 * d->length;
    // bit_length = ft_bswap64(bit_length);
    ft_memcpy(((uint8_t *)d->msg) + new_length + 4, &bit_length, 4);
    // d->msg[(d->length)] = bit_length;
	d->length = new_length + 8;
    // ft_bswap64_v(&n);
    // ft_putbytes(&n, 5, 0);
    // ft_putchar('\n');
    // ft_putchar('\n');
    // ft_putbytes(d->msg, d->length, '\n');
    // ft_putchar('\n');
    // ft_putchar('\n');
}

static void op_loop(t_sha256 *d, uint32_t i)
{
    uint32_t    tmp1;
    uint32_t    tmp2;




    // uint32_t S1 = BSIG1(d->e);
    // uint32_t ch = CH(d->e, d->f, d->g);
    // uint32_t k = g_k_s256[i];<not available>
    // uint32_t w = d->msgsched[i];
    // tmp1 = d->h + S1 + ch + k + w;
    tmp1 = d->h + BSIG1(d->e) + CH(d->e, d->f, d->g) + g_k_s256[i] + d->msgsched[i];
    tmp2 = BSIG0(d->a) + MAJ(d->a, d->b, d->c);
    d->h = d->g;
    d->g = d->f;
    d->f = d->e;
    d->e = d->d + tmp1;
    d->d = d->c;
    d->c = d->b;
    d->b = d->a;
    d->a = tmp1 + tmp2;
    // printf("comp =  %i \t %08x \t %08x \t %08x \t %08x \t %08x \t %08x \t %08x \t %08x \n",
    //     i, d->a, d->b, d->c, d->d, d->e, d->f, d->g, d->h);
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
        // ft_memcpy(d->msgsched + j, &tmp, 1);
        // ft_putbytes(&tmp, 1, 0);
        // ft_putchar('\n');
        j++;
    }
    // ft_putendl("msgsched = ");
    // ft_putbytes_array(d->msgsched, sizeof(uint32_t) * 16, sizeof(uint64_t), "\n ");
    // ft_putchar('\n');
    // ft_putchar('\n');
    d->a = d->h0;
    d->b = d->h1;
    d->c = d->h2;
    d->d = d->h3;
    d->e = d->h4;
    d->f = d->h5;
    d->g = d->h6;
    d->h = d->h7;
    // printf("\t\t a \t\t b \t\t c \t\t d \t\t e \t\t f \t\t g \t\t h \n");
    // printf("init: \t\t %x \t %x \t %x \t %x \t %x \t %x \t %x \t %x \n",
    //     d->a, d->b, d->c, d->d, d->e, d->f, d->g, d->h);
    j = 0;
    while (j < 64)
        op_loop(d, j++);
    // printf("h    =  %i \t %08x \t %08x \t %08x \t %08x \t %08x \t %08x \t %08x \t %08x \n",
        // i, d->a, d->b, d->c, d->d, d->e, d->f, d->g, d->h);
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
	ft_uitoa(d->h0, digest, 16);
	ft_uitoa(d->h1, digest + 8, 16);
	ft_uitoa(d->h2, digest + 16, 16);
	ft_uitoa(d->h3, digest + 24, 16);
	ft_uitoa(d->h4, digest + 32, 16);
	ft_uitoa(d->h5, digest + 40, 16);
	ft_uitoa(d->h6, digest + 48, 16);
	ft_uitoa(d->h7, digest + 56, 16);
    digest[64] = 0;
    free(d->msg);
    free(d);
	return (digest);
}
