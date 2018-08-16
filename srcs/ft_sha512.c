/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha512.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 16:03:15 by gwood             #+#    #+#             */
/*   Updated: 2018/08/16 14:33:09 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha512.h"
#include "ft_bswap_utils.h"

static t_sha512	*init(void)
{
	t_sha512 *ret;

	ret = (t_sha512 *)ft_memalloc(sizeof(t_sha512));
	ret->head[0] = 0x6a09e667f3bcc908;
	ret->head[1] = 0xbb67ae8584caa73b;
	ret->head[2] = 0x3c6ef372fe94f82b;
	ret->head[3] = 0xa54ff53a5f1d36f1;
	ret->head[4] = 0x510e527fade682d1;
	ret->head[5] = 0x9b05688c2b3e6c1f;
	ret->head[6] = 0x1f83d9abfb41bd6b;
	ret->head[7] = 0x5be0cd19137e2179;
	ret->msg = NULL;
	ret->msgsched = NULL;
	return (ret);
}

static void		padding(t_sha512 *d, t_byte *message)
{
	uint32_t	i;
	size_t		new_length;
	uint64_t	bit_length;

	new_length = d->length * 8 + 1;
	while (new_length % 1024 != 896)
		new_length++;
	new_length /= 8;
	d->msg = (uint64_t *)ft_memalloc(new_length + 128);
	ft_memcpy(d->msg, message, d->length);
	((uint8_t *)d->msg)[d->length] = 128;
	i = 0;
	while (i < ((8 * (new_length + 16) / 1024) * 16) - 1)
		ft_bswap64_v(&(d->msg[i++]));
	bit_length = (uint64_t)8 * d->length;
	ft_memcpy(((uint8_t *)d->msg) + new_length + 8, &bit_length, 8);
	d->length = new_length + 16;
}

static void		op_loop(t_sha512 *d, uint32_t i)
{
	uint64_t	tmp1;
	uint64_t	tmp2;

	tmp1 = d->wvars[7] + BSIG164(d->wvars[4]) + CH64(d->wvars[4], d->wvars[5],
		d->wvars[6]) + g_k_s512[i] + d->msgsched[i];
	tmp2 = BSIG064(d->wvars[0]) + MAJ64(d->wvars[0], d->wvars[1], d->wvars[2]);
	d->wvars[7] = d->wvars[6];
	d->wvars[6] = d->wvars[5];
	d->wvars[5] = d->wvars[4];
	d->wvars[4] = d->wvars[3] + tmp1;
	d->wvars[3] = d->wvars[2];
	d->wvars[2] = d->wvars[1];
	d->wvars[1] = d->wvars[0];
	d->wvars[0] = tmp1 + tmp2;
}

static void		chunk_loop(t_sha512 *d, uint32_t i)
{
	int	j;

	d->msgsched = (uint64_t *)ft_memalloc(sizeof(uint64_t) * 80);
	ft_memcpy(d->msgsched, d->msg + i * 16, sizeof(uint64_t) * 16);
	j = 16;
	while (j < 80)
	{
		d->msgsched[j] = d->msgsched[j - 16] +
			SSIG064(d->msgsched[j - 15]) + d->msgsched[j - 7] +
			SSIG164(d->msgsched[j - 2]);
		j++;
	}
	j = -1;
	while (++j < 8)
		d->wvars[j] = d->head[j];
	j = 0;
	while (j < 80)
		op_loop(d, j++);
	j = -1;
	while (j++ < 8)
		d->head[j] += d->wvars[j];
	free(d->msgsched);
}

char			*ft_sha512(t_byte *message, size_t length)
{
	uint32_t	i;
	t_sha512	*d;
	char		*digest;

	d = init();
	d->length = length;
	padding(d, message);
	i = 0;
	while (i < d->length / 128)
		chunk_loop(d, i++);
	digest = ft_strnew(128);
	i = 0;
	while (i < 8)
		digest = ft_strjoinfree(digest, ft_ultoa(d->head[i++], 16), 3);
	digest[128] = 0;
	free(d->msg);
	free(d);
	return (digest);
}
