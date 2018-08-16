/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 16:03:15 by gwood             #+#    #+#             */
/*   Updated: 2018/08/16 14:31:39 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha256.h"
#include "ft_bswap_utils.h"

static t_sha256	*init(void)
{
	t_sha256 *ret;

	ret = (t_sha256 *)ft_memalloc(sizeof(t_sha256));
	ret->head[0] = 0x6a09e667;
	ret->head[1] = 0xbb67ae85;
	ret->head[2] = 0x3c6ef372;
	ret->head[3] = 0xa54ff53a;
	ret->head[4] = 0x510e527f;
	ret->head[5] = 0x9b05688c;
	ret->head[6] = 0x1f83d9ab;
	ret->head[7] = 0x5be0cd19;
	ret->msg = NULL;
	ret->msgsched = NULL;
	return (ret);
}

static void		padding(t_sha256 *d, t_byte *message)
{
	uint32_t	i;
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
	while (i < ((8 * (new_length + 8) / 512) * 16) - 1)
		ft_bswap32_v(&(d->msg[i++]));
	bit_length = (uint32_t)8 * d->length;
	ft_memcpy(((uint8_t *)d->msg) + new_length + 4, &bit_length, 4);
	d->length = new_length + 8;
}

static void		op_loop(t_sha256 *d, uint32_t i)
{
	uint32_t	tmp1;
	uint32_t	tmp2;

	tmp1 = d->wvars[7] + BSIG1(d->wvars[4]) + CH(d->wvars[4], d->wvars[5],
		d->wvars[6]) + g_k_s256[i] + d->msgsched[i];
	tmp2 = BSIG0(d->wvars[0]) + MAJ(d->wvars[0], d->wvars[1], d->wvars[2]);
	d->wvars[7] = d->wvars[6];
	d->wvars[6] = d->wvars[5];
	d->wvars[5] = d->wvars[4];
	d->wvars[4] = d->wvars[3] + tmp1;
	d->wvars[3] = d->wvars[2];
	d->wvars[2] = d->wvars[1];
	d->wvars[1] = d->wvars[0];
	d->wvars[0] = tmp1 + tmp2;
}

static void		chunk_loop(t_sha256 *d, uint32_t i)
{
	int	j;

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
	j = -1;
	while (++j < 8)
		d->wvars[j] = d->head[j];
	j = 0;
	while (j < 64)
		op_loop(d, j++);
	j = -1;
	while (j++ < 8)
		d->head[j] += d->wvars[j];
	free(d->msgsched);
}

char			*ft_sha256(t_byte *message, size_t length)
{
	uint32_t	i;
	t_sha256	*d;
	char		*digest;

	d = init();
	d->length = length;
	padding(d, message);
	i = 0;
	while (i < d->length / 64)
		chunk_loop(d, i++);
	digest = ft_strnew(64);
	i = 0;
	while (i < 8)
		digest = ft_strjoinfree(digest, ft_uitoa(d->head[i++], 16), 3);
	digest[64] = 0;
	free(d->msg);
	free(d);
	return (digest);
}
