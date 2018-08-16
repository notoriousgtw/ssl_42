/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 12:57:55 by gwood             #+#    #+#             */
/*   Updated: 2018/08/16 14:29:29 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# define SSL_BUFF_SIZE 500
# define INPUT_STDIN 0
# define INPUT_STRING 1
# define INPUT_FILE 2
# define FT_ERROR_UNKNOWN "ft_ssl: Error: "

typedef void				(*t_ft_ssl_cmd)(int argc, char **argv);

typedef struct				s_ft_ssl_input
{
	int						input_type;
	char					*filename;
	char					*input;
	size_t					input_len;
	char					*output;
	struct s_ft_ssl_input	*next;
}							t_ft_ssl_input;
typedef struct				s_ft_ssl_prg
{
	char				*name;

	t_ft_ssl_cmd		ssl_fnc;
}							t_ft_ssl_prg;

void						ft_ssl_md5(int argc, char **argv);
void						ft_ssl_sha256(int argc, char **argv);
void						ft_ssl_sha224(int argc, char **argv);
void						ft_ssl_sha512(int argc, char **argv);
void						ft_ssl_sha384(int argc, char **argv);

static const t_ft_ssl_prg	g_ft_ssl_program_list[] = {
	{"md5", &ft_ssl_md5},
	{"sha256", &ft_ssl_sha256},
	{"sha224", &ft_ssl_sha224},
	{"sha512", &ft_ssl_sha512},
	{"sha384", &ft_ssl_sha384},
	{NULL, NULL}
};

void						ft_ssl_error_invalid_command(char *cmd);

void						add_input(t_ft_ssl_input **inputs,
								t_ft_ssl_input *input);
t_ft_ssl_input				*new_input(void);
void						del_inputs(t_ft_ssl_input **inputs);

#endif
