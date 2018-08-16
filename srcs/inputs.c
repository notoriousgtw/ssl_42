/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 15:39:29 by gwood             #+#    #+#             */
/*   Updated: 2018/08/16 14:08:31 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			add_input(t_ft_ssl_input **inputs, t_ft_ssl_input *input)
{
	input->next = *inputs;
	*inputs = input;
}

t_ft_ssl_input	*new_input(void)
{
	t_ft_ssl_input *ret;

	if (!(ret = (t_ft_ssl_input *)ft_memalloc(sizeof(t_ft_ssl_input))))
		return (NULL);
	ret->input_type = -1;
	ret->filename = NULL;
	ret->input = NULL;
	ret->input_len = 0;
	ret->next = NULL;
	return (ret);
}

void			del_inputs(t_ft_ssl_input **inputs)
{
	t_ft_ssl_input *tmp;
	t_ft_ssl_input *lst;

	lst = *inputs;
	while (lst != NULL)
	{
		tmp = lst->next;
		ft_strdel(&lst->input);
		ft_strdel(&lst->filename);
		ft_strdel(&lst->output);
		free(lst);
		lst = tmp;
	}
}
