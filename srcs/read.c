/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 13:29:09 by gwood             #+#    #+#             */
/*   Updated: 2018/08/08 19:24:34 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include <stdio.h>

static void             add_input(t_ft_ssl_data *d, t_ft_ssl_input *input)
{
    if (d->inputs == NULL)
        d->inputs = ft_lstnew(input, sizeof(t_ft_ssl_input));
    else
        ft_lstadd(&d->inputs, ft_lstnew(input, sizeof(t_ft_ssl_input)));
}

static t_ft_ssl_input   *new_input()
{
    t_ft_ssl_input *ret;

    if (!(ret = (t_ft_ssl_input *)ft_memalloc(sizeof(t_ft_ssl_input))))
		return (NULL);
    ret->input_type = -1;
    ret->filename = NULL;
    ret->msg = NULL;
    ret->msg_len = 0;
    ret->digest = NULL;
    return (ret);
}

void                    ft_ssl_read_stdin(t_ft_ssl_data *d)
{
    int             check;
    char            buf[SSL_BUFF_SIZE + 1];
    t_ft_ssl_input  *input;

    input = new_input();
    input->input_type = INPUT_STDIN;
    input->msg = ft_strnew(0);
    while((check = read(0, &buf, SSL_BUFF_SIZE)) > 0)
    {
		buf[check] = 0;
        input->msg =
            ft_strjoinfree(input->msg, buf, 1);
        input->msg_len += check;
		ft_bzero(buf, SSL_BUFF_SIZE + 1);
    }
    if (check < 0)
        ft_error_unknown();

    if (d->p)
        ft_putendl(input->msg);
    add_input(d, input);
}

void                    ft_ssl_read_string(t_ft_ssl_data *d)
{
    t_ft_ssl_input  *input;

    input = new_input();
    input->input_type = INPUT_STRING;
    input->msg = d->arg_str;
    input->msg_len = ft_strlen(d->arg_str);
    add_input(d, input);
}

void                    ft_ssl_read_file(t_ft_ssl_data *d, char *path)
{
    int     fd;
    int     check;
    char    buf[SSL_BUFF_SIZE + 1];
    t_ft_ssl_input  *input;

    input = new_input();
    input->input_type = INPUT_FILE;
    if ((fd = open(path, O_RDONLY)) < 0)
    {
        input->digest = ft_strjoin((char *)path, " is not a valid file");
        add_input(d, input);
        return ;
    }
    input->filename = path;
    input->msg = ft_strnew(0);
    while((check = read(fd, &buf, SSL_BUFF_SIZE)) > 0)
    {
		buf[check] = 0;
        input->msg = ft_strjoinfree(input->msg, buf, 1);
        input->msg_len += check;
		ft_bzero(buf, SSL_BUFF_SIZE + 1);
    }
    if (check < 0)
        ft_error_unknown();
    add_input(d, input);
}
