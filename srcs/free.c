/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 14:32:22 by gwood             #+#    #+#             */
/*   Updated: 2018/08/09 16:35:45 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"

void    del_input(t_list *elem)
{
    t_ft_ssl_input *input;

    input = (t_ft_ssl_input *)elem->content;
    ft_strdel(&input->msg);
    ft_strdel(&input->filename);
    ft_strdel(&input->digest);
    free(input);
}

void    ft_ssl_free_data(t_ft_ssl_data *d)
{
    ft_lstiter(d->inputs, del_input);
    ft_lstdel(&(d->inputs), NULL);
    free(d);
}
