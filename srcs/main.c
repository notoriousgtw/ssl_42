/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 21:12:33 by gwood             #+#    #+#             */
/*   Updated: 2018/08/09 14:09:28 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include "stdio.h"

void			parse_args(t_ft_ssl_data *d, int argc, char **argv)
{
    int i;
	uint32_t cnt;

	cnt = 0;
    i = 2;
    while (i < argc)
    {
        if (!d->s && !d->p && ft_strcmp("-p", argv[i]) == 0 && ++cnt)
            d->p = true;
        else if (!d->s && !d->q && ft_strcmp("-q", argv[i]) == 0 && ++cnt)
            d->q = true;
        else if (!d->s && !d->r && ft_strcmp("-r", argv[i]) == 0 && ++cnt)
            d->r = true;
        else if (!d->s && ft_strcmp("-s", argv[i]) == 0)
		{
			if (++i >= argc)
				ft_error("please provide a string");
			d->arg_str = argv[i];
            d->s = true;
			cnt += 2;
		}
		else
		{
			d->f = true;
			break;
		}
		i++;
    }
	d->arg_ind = 2 + cnt;
}

t_ft_ssl_data   *init(char *ssl_prg)
{
	int				i;
    t_ft_ssl_data	*ret;

	if (!(ret = (t_ft_ssl_data *)ft_memalloc(sizeof(t_ft_ssl_data))))
		return (NULL);
	ret->p = false;
	ret->q = false;
	ret->r = false;
	ret->s = false;
	ret->f = false;
	ret->arg_str = NULL;
	ret->arg_ind = 0;
	ret->inputs = NULL;
	ret->ssl_prg = NULL;
	i = 0;
    while (g_ft_ssl_program_list[i].type != NULL)
    {
        if (!(ft_strcmp(g_ft_ssl_program_list[i].type, ssl_prg)))
            ret->ssl_prg = &(((t_ft_ssl_prg *)g_ft_ssl_program_list)[i]);
        i++;
    }
	if (ssl_prg == NULL)
		ft_ssl_error_prg(ssl_prg);
	return (ret);
}

void	msg_iter(t_list *elem, void *data)
{
	t_ft_ssl_data	*d;
	t_ft_ssl_input	*cast;

	d = (t_ft_ssl_data *)data;
	cast = (t_ft_ssl_input *)elem->content;
	if (cast->msg != NULL)
		d->ssl_prg->ssl_fnc((t_byte *)cast->msg, cast->digest, cast->msg_len);
	print_digest(d, cast);
}

int	main(int argc, char **argv)
{
	int i;
	t_ft_ssl_data   *d;

	if (argc > 1 && argv[1] != NULL)
	{
		if ((d = init(argv[1])) == NULL)
			ft_error("malloc error");
		parse_args(d, argc, argv);
		if ((!d->s && !d->f) || d->p)
			ft_ssl_read_stdin(d);
		if (d->s)
			ft_ssl_read_string(d);
		if (d->f)
		{
			i = d->arg_ind;
			while (i < argc)
				ft_ssl_read_file(d, argv[i++]);
		}
		ft_lstiter_data(d->inputs, msg_iter, d);
	}
}
