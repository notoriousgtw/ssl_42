/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 21:12:33 by gwood             #+#    #+#             */
/*   Updated: 2018/07/22 21:41:12 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <inttypes.h>
#include <stdio.h>
#include "libft/libft.h"

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

static void	padding(char *message, size_t *length, uint8_t **msg)
{
	size_t		new_length;
    uint64_t	bit_length;

    new_length = *length * 8 + 1;
    while (new_length % 512 != 448)
	{
    	new_length++;
	}
	// ft_putstr("bits = ");
    // ft_putnbr(new_length);
    // ft_putchar('\n');
    new_length /= 8;
	// ft_putstr("bytes = ");
    // ft_putnbr(new_length);
    // ft_putchar('\n');
    *msg = (uint8_t *)ft_memalloc(new_length + 64);
    ft_memcpy(*msg, message, *length);
    (*msg)[*length] = 128;
	ft_putbits(*msg, new_length);
    ft_putchar('\n');
    ft_putchar('\n');
    bit_length = (uint64_t)8 * *length;
	ft_putbits(&bit_length, sizeof(bit_length));
    ft_putchar('\n');
    ft_putchar('\n');
    ft_memcpy((*msg) + new_length, &bit_length, 8);
	ft_putbits(*msg, new_length);
    ft_putchar('\n');
    ft_putchar('\n');
	*length = new_length + 8;
}

typedef struct	s_opdata
{
	uint32_t	a;
    uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	k;
	uint32_t	s;
	uint32_t	i;
}				t_opdata;

typedef struct	s_md5
{
	uint32_t	a;
    uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t 	(*op)(uint32_t x, uint32_t y, uint32_t z);
}				t_md5;

static uint32_t f(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) | ((-x) & z);
}

static uint32_t g(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) | (x & (-z));
}

static uint32_t h(uint32_t x, uint32_t y, uint32_t z)
{
	return x ^ y ^ z;
}

static uint32_t i(uint32_t x, uint32_t y, uint32_t z)
{
	return y | (x | (-z));
}

char		*ft_md5(char *message)
{
	char 		*digest = NULL;
	size_t		length;
	uint8_t		*msg;
	uint32_t 	i;
	uint32_t 	f;
	uint32_t 	g;
	uint32_t 	offset;
	uint32_t	tmp;
	uint32_t 	*words;
    uint32_t	s[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
						 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
						 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
						 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
    uint32_t	K[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
						 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
						 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
						 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
						 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
						 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
						 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
						 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
						 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
						 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
						 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
						 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
						 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
						 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
						 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
						 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
	uint32_t	h0 = 0x67452301;
	uint32_t	h1 = 0xefcdab89;
	uint32_t	h2 = 0x98badcfe;
	uint32_t	h3 = 0x10325476;
	msg = NULL;
	length = ft_strlen(message);
    padding(message, &length, &msg);
	offset = 0;
	while (offset < length)
	{
		words = (uint32_t *) (msg + offset);
		offset += 512 / 8;
		a = h0;
		b = h1;
		c = h2;
		d = h3;
		i = -1;
		while (++i < 64)
		{
			if (i < 16)
			{
				f = (b & c) | ((-b) & d);
				g = i;
			}
			else if (i < 32)
			{
				f = (d & b) | ((-d) & c);
				g = (5 * i + 1) % 16;
			}
			else if (i < 48)
			{
				f = b ^ c ^ d;
				g = (3 * i + 5) % 16;
			}
			else
			{
				f = c ^ (b | (-d));
				g = (7 * i) % 16;
			}
			tmp = d;
			d = c;
			c = b;
			b = b + LEFTROTATE((a + f + K[i] + words[g]), s[i]);
			a = tmp;
		}
		h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
	}
	digest = ft_uitoa_base(h0, 16);
	digest = ft_strcat(digest, ft_uitoa_base(h1, 16));
	digest = ft_strcat(digest, ft_uitoa_base(h2, 16));
	digest = ft_strcat(digest, ft_uitoa_base(h3, 16));
	return (digest);
}

void		display_usage(char *name)
{
    ft_putstr("usage: ");
    ft_putstr(name);
    ft_putendl(" message");
}


int			main(int argc, char *argv[])
{
	if (argc == 2)
	{
		ft_putstr(ft_md5(argv[1]));
		// ft_md5(argv[1]);
	}
	else
		display_usage(*argv);
	return (0);
}
