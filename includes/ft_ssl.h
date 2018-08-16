/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 12:57:55 by gwood             #+#    #+#             */
/*   Updated: 2018/08/15 16:38:00 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# define SSL_BUFF_SIZE 16
# define INPUT_STDIN 0
# define INPUT_STRING 1
# define INPUT_FILE 2
# define FT_ERROR_UNKNOWN "ft_ssl: Error: "

typedef int					(*t_ft_ssl_cmd)(int argc, char **argv);

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


typedef struct				s_ft_ssl_data
{
	t_ft_ssl_prg	*ssl_prg;
}							t_ft_ssl_data;

int							ft_ssl_sha256(int argc, char **argv);

static const t_ft_ssl_prg	g_ft_ssl_program_list[3] = {
	{"sha256", &ft_ssl_sha256},
	{NULL, NULL}
};

void						ft_ssl_error_invalid_command(char *cmd);

void						add_input(t_ft_ssl_input **inputs,
								t_ft_ssl_input *input);
t_ft_ssl_input				*new_input(void);
void						del_inputs(t_ft_ssl_input **inputs);

#endif
