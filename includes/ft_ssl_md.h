/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 13:18:05 by gwood             #+#    #+#             */
/*   Updated: 2018/08/16 12:58:23 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA256_H
# define FT_SSL_SHA256_H

# include "ft_md5.h"
# include "ft_sha256.h"
# include "ft_sha224.h"
# include "ft_sha512.h"
# include "ft_sha384.h"
# include "ft_getopts.h"

typedef char					*(*t_ft_ssl_md_fnc)(t_byte *msg, size_t msg_len);

typedef struct	s_ft_ssl_input	t_ft_ssl_input;

typedef struct					s_ft_ssl_md_data
{
	t_bool			p;
	t_bool			r;
	t_bool			q;
	t_bool			s;
	t_bool			f;
	char			*name;
	t_opts			*opts;
	size_t			arg_ind;
	char			*arg_str;
	t_ft_ssl_md_fnc	md;

	t_ft_ssl_input	*inputs;
}								t_ft_ssl_md_data;



void							ft_ssl_md_read_stdin(t_ft_ssl_md_data *d);
void							ft_ssl_md_read_string(t_ft_ssl_md_data *d);
void							ft_ssl_md_read_file(t_ft_ssl_md_data *d,
									char *path);

void							print_digest(t_ft_ssl_md_data *d,
									t_ft_ssl_input *input);

void							ft_ssl_md_error_invalid_command(
									t_ft_ssl_md_data *d,
									char *prg);

t_ft_ssl_md_data				*ft_ssl_md(int argc, char **argv,
									t_ft_ssl_md_fnc md);

void							ft_ssl_md_error_no_string(t_ft_ssl_md_data *d);
void							ft_ssl_md_error_invalid_file(
									t_ft_ssl_md_data *d,
									char *filename);

void							ft_ssl_md_free_data(t_ft_ssl_md_data *d);

#endif
