/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha384.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 16:03:15 by gwood             #+#    #+#             */
/*   Updated: 2018/08/16 13:04:47 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha384.h"
#include "ft_bswap_utils.h"
#include <stdio.h>

static t_sha384	*init(void)
{
	t_sha384 *ret;

	ret = (t_sha384 *)ft_memalloc(sizeof(t_sha384));
	ret->head[0] = 0xcbbb9d5dc1059ed8;
	ret->head[1] = 0x629a292a367cd507;
	ret->head[2] = 0x9159015a3070dd17;
	ret->head[3] = 0x152fecd8f70e5939;
	ret->head[4] = 0x67332667ffc00b31;
	ret->head[5] = 0x8eb44a8768581511;
	ret->head[6] = 0xdb0c2e0d64f98fa7;
	ret->head[7] = 0x47b5481dbefa4fa4;
	ret->msg = NULL;
	ret->msgsched = NULL;
	return (ret);
}

static void		padding(t_sha384 *d, t_byte *message)
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

static void		op_loop(t_sha384 *d, uint32_t i)
{
	uint64_t	tmp1;
	uint64_t	tmp2;

	tmp1 = d->wvars[7] + BSIG164(d->wvars[4]) + CH64(d->wvars[4], d->wvars[5],
		d->wvars[6]) + g_k_s384[i] + d->msgsched[i];
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

static void		chunk_loop(t_sha384 *d, uint32_t i)
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

char			*ft_sha384(t_byte *message, size_t length)
{
	uint32_t	i;
	t_sha384	*d;
	char		*digest;

	d = init();
	d->length = length;
	padding(d, message);
	i = 0;
	while (i < d->length / 128)
		chunk_loop(d, i++);
	digest = ft_strnew(128);
	i = 0;
	while (i < 6)
		digest = ft_strjoinfree(digest, ft_ultoa(d->head[i++], 16), 3);
	digest[128] = 0;
	free(d->msg);
	free(d);
	return (digest);
}
