/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 13:29:09 by gwood             #+#    #+#             */
/*   Updated: 2018/08/08 17:13:30 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"

static t_ft_ssl_input   *new_input()
{
    t_ft_ssl_input *ret;

    if (!(ret = (t_ft_ssl_input *)ft_memalloc(sizeof(t_ft_ssl_input))))
		return (NULL);
    ret->msg = NULL;
    ret->msg_len = 0;
    ret->digest = NULL;
    return (ret);
}

void                    ft_ssl_read_file(t_ft_ssl_data *d, const char *path)
{
    int     fd;
    int     check;
    char    buf[SSL_BUFF_SIZE + 1];
    t_ft_ssl_input  *input;

    if ((fd = open(path, O_RDONLY)) < 0)
        ft_error(ft_strcat((char *)path, " is not a valid file"));
    input = new_input();
    input->msg = ft_strnew(0);
    while((check = read(fd, &buf, SSL_BUFF_SIZE)) > 0)
    {
		buf[check] = 0;
        input->msg =
            ft_strjoinfree(input->msg, buf, 1);
        input->msg_len += check;
		ft_bzero(buf, SSL_BUFF_SIZE + 1);
    }
    if (check < 0)
        ft_error_unknown();
    input->digest = NULL;
    if (d->inputs == NULL)
        d->inputs = ft_lstnew(input, sizeof(t_ft_ssl_input));
    else
        ft_lstapp(&d->inputs, ft_lstnew(input, sizeof(t_ft_ssl_input)));
    d->input_count++;
}

void                    ft_ssl_read_stdin(t_ft_ssl_data *d)
{
    int             check;
    char            buf[SSL_BUFF_SIZE + 1];
    t_ft_ssl_input  *input;

    input = new_input();
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
    input->digest = NULL;
    if (d->inputs == NULL)
        d->inputs = ft_lstnew(input, sizeof(t_ft_ssl_input));
    else
        ft_lstapp(&d->inputs, ft_lstnew(input, sizeof(t_ft_ssl_input)));
    d->input_count++;
}

void                    ft_ssl_read_string(t_ft_ssl_data *d)
{
    t_ft_ssl_input  *input;

    input = new_input();
    input->msg = d->arg_iter;
    input->msg_len = ft_strlen(d->arg_iter);
    input->digest = NULL;
    if (d->inputs == NULL)
        d->inputs = ft_lstnew(input, sizeof(t_ft_ssl_input));
    else
        ft_lstapp(&d->inputs, ft_lstnew(input, sizeof(t_ft_ssl_input)));
    d->input_count++;
}
