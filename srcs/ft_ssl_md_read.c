/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 13:29:09 by gwood             #+#    #+#             */
/*   Updated: 2018/08/16 12:45:34 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_md.h"

void					ft_ssl_md_read_stdin(t_ft_ssl_md_data *d)
{
	int				check;
	char			buf[SSL_BUFF_SIZE + 1];
	t_ft_ssl_input	*input;

	input = new_input();
	input->input_type = INPUT_STDIN;
	input->input = ft_strnew(0);
	while ((check = read(0, &buf, SSL_BUFF_SIZE)) > 0)
	{
		buf[check] = 0;
		input->input_len += check;
		input->input = ft_strjoinfree(input->input, buf, 1);
		ft_bzero(buf, SSL_BUFF_SIZE + 1);
	}
	if (check < 0)
		ft_error_unknown_free(FT_ERROR_UNKNOWN,
			(t_free_fnc)ft_ssl_md_free_data, d);
	if (d->p)
		ft_putstr(input->input);
	add_input(&(d->inputs), input);
}

void					ft_ssl_md_read_string(t_ft_ssl_md_data *d)
{
	t_ft_ssl_input	*input;

	input = new_input();
	input->input_type = INPUT_STRING;
	input->input = d->arg_str;
	input->input_len = ft_strlen(d->arg_str);
	add_input(&(d->inputs), input);
}

void					ft_ssl_md_read_file(t_ft_ssl_md_data *d, char *path)
{
	int				fd;
	int				check;
	char			buf[SSL_BUFF_SIZE + 1];
	t_ft_ssl_input	*input;

	input = new_input();
	input->input_type = INPUT_FILE;
	input->filename = ft_strdup(path);
	if ((fd = open(path, O_RDONLY)) < 0)
	{
		add_input(&(d->inputs), input);
		return ;
	}
	input->input = ft_strnew(0);
	while ((check = read(fd, &buf, SSL_BUFF_SIZE)) > 0)
	{
		buf[check] = 0;
		input->input_len += check;
		input->input = ft_strjoinfree(input->input, buf, 1);
		ft_bzero(buf, SSL_BUFF_SIZE + 1);
	}
	if (check < 0)
		ft_error_unknown_free(FT_ERROR_UNKNOWN,
			(t_free_fnc)ft_ssl_md_free_data, d);
	add_input(&(d->inputs), input);
}
