/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 14:32:22 by gwood             #+#    #+#             */
/*   Updated: 2018/08/09 18:22:04 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"

static void    del_inputs(t_ft_ssl_input **inputs)
{
    t_ft_ssl_input *tmp;
    t_ft_ssl_input *lst;

    lst = *inputs;
    while (lst != NULL)
    {
        tmp = lst->next;
        ft_strdel(&lst->msg);
        ft_strdel(&lst->filename);
        ft_strdel(&lst->digest);
        free(lst);
        lst = tmp;
    }
}

void            ft_ssl_free_data(t_ft_ssl_data *d)
{
    del_inputs(&d->inputs);
    free(d);
}
