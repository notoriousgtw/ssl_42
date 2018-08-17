/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 16:03:15 by gwood             #+#    #+#             */
/*   Updated: 2018/08/17 14:13:35 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

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

static void		padding(t_md5 *d, t_byte *message)
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

static void		op(t_md5 *d, uint32_t i, uint32_t *f, uint32_t *g)
{
	if (i < 16)
	{
		*f = F(d->b, d->c, d->d);
		*g = i;
	}
	else if (i < 32)
	{
		*f = G(d->b, d->c, d->d);
		*g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		*f = H(d->b, d->c, d->d);
		*g = (3 * i + 5) % 16;
	}
	else
	{
		*f = I(d->b, d->c, d->d);
		*g = (7 * i) % 16;
	}
}

static void		word_loop(t_md5 *d)
{
	uint32_t	i;
	uint32_t	f;
	uint32_t	g;

	d->words = (uint32_t *)(d->msg + d->offset);
	d->offset += 64;
	d->a = d->h0;
	d->b = d->h1;
	d->c = d->h2;
	d->d = d->h3;
	i = -1;
	while (++i < 64)
	{
		op(d, i, &f, &g);
		f = f + d->a + g_k[i] + d->words[g];
		d->a = d->d;
		d->d = d->c;
		d->c = d->b;
		d->b = d->b + ROTL(f, g_s[i]);
	}
	d->h0 += d->a;
	d->h1 += d->b;
	d->h2 += d->c;
	d->h3 += d->d;
}

char			*ft_md5(t_byte *message, size_t length)
{
	t_md5	*d;
	char	*digest;

	d = init();
	d->length = length;
	padding(d, message);
	while (d->offset < d->length)
		word_loop(d);
	digest = ft_strnew(32);
	digest = ft_strjoinfree(digest, ft_uitoa(ft_bswap32(d->h0), 16), 3);
	digest = ft_strjoinfree(digest, ft_uitoa(ft_bswap32(d->h1), 16), 3);
	digest = ft_strjoinfree(digest, ft_uitoa(ft_bswap32(d->h2), 16), 3);
	digest = ft_strjoinfree(digest, ft_uitoa(ft_bswap32(d->h3), 16), 3);
	digest[32] = 0;
	free(d->msg);
	free(d);
	return (digest);
}
