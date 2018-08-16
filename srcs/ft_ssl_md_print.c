/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:18:25 by gwood             #+#    #+#             */
/*   Updated: 2018/08/15 17:57:01 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_md.h"

static void	put_digest(t_ft_ssl_md_data *d, t_ft_ssl_input *input)
{
	if (input->input_type == INPUT_STDIN)
		ft_putendl(input->output);
	else if (input->input_type == INPUT_STRING)
	{
		ft_putstr(d->name);
		ft_putstr(" (\"");
		ft_putstr(input->input);
		ft_putstr("\") = ");
		ft_putendl(input->output);
	}
	else if (input->input_type == INPUT_FILE)
	{
		if (input->output == NULL)
			ft_ssl_md_error_invalid_file(d, input->filename);
		else if (input->filename != NULL)
		{
			ft_putstr(d->name);
			ft_putstr(" (");
			ft_putstr(input->filename);
			ft_putstr(") = ");
			ft_putendl(input->output);
		}
	}
}

static void	put_digest_rev(t_ft_ssl_md_data *d, t_ft_ssl_input *input)
{
	if (input->input_type == INPUT_STDIN)
		ft_putendl(input->output);
	else if (input->input_type == INPUT_STRING)
	{
		ft_putstr(input->output);
		ft_putstr(" \"");
		ft_putstr(input->input);
		ft_putendl("\"");
	}
	else if (input->input_type == INPUT_FILE)
	{
		if (input->output == NULL)
			ft_ssl_md_error_invalid_file(d, input->filename);
		else if (input->filename != NULL)
		{
			ft_putstr(input->output);
			ft_putchar(' ');
			ft_putendl(input->filename);
		}
		else
			ft_putendl(input->output);
	}
}

void		print_digest(t_ft_ssl_md_data *d, t_ft_ssl_input *input)
{
	if (!d->q)
	{
		if (!d->r)
			put_digest(d, input);
		else
			put_digest_rev(d, input);
	}
	else
	{
		ft_putendl(input->output);
	}
}
