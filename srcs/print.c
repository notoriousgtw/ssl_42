/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:18:25 by gwood             #+#    #+#             */
/*   Updated: 2018/08/09 18:22:24 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"

static void    put_digest(t_ft_ssl_data *d, t_ft_ssl_input *input)
{
    if (input->input_type == INPUT_STDIN)
        ft_putendl(input->digest);
    else if (input->input_type == INPUT_STRING)
    {
        ft_putstr(d->ssl_prg->name);
        ft_putstr(" (\"");
        ft_putstr(input->msg);
        ft_putstr("\") = ");
        ft_putendl(input->digest);
    }
    else if (input->input_type == INPUT_FILE)
    {
        if (input->filename != NULL)
        {
            ft_putstr(d->ssl_prg->name);
            ft_putstr(" (");
            ft_putstr(input->filename);
            ft_putstr(") = ");
        }
        ft_putendl(input->digest);
    }
}

static void    put_digest_rev(t_ft_ssl_input *input)
{
    if (input->input_type == INPUT_STDIN)
        ft_putendl(input->digest);
    else if (input->input_type == INPUT_STRING)
    {
        ft_putstr(input->digest);
        ft_putstr(" \"");
        ft_putstr(input->msg);
        ft_putendl("\"");
    }
    else if (input->input_type == INPUT_FILE)
    {
        if (input->filename != NULL)
        {
            ft_putstr(input->digest);
            ft_putchar(' ');
            ft_putendl(input->filename);
        }
        else
            ft_putendl(input->digest);
    }
}

void	print_digest(t_ft_ssl_data *d, t_ft_ssl_input *input)
{
	if (!d->q)
	{
		if (!d->r)
            put_digest(d, input);
		else
			put_digest_rev(input);
	}
	else
	{
		ft_putendl(input->digest);
	}
}
