/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 13:06:40 by gwood             #+#    #+#             */
/*   Updated: 2018/08/16 13:58:15 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_md.h"

void					ft_ssl_md_free_data(t_ft_ssl_md_data *d)
{
	del_inputs(&d->inputs);
	ft_freeopts(&d->opts);
	ft_strdel(&d->name);
	free(d);
}

static void				parse_opts(t_ft_ssl_md_data *d, t_opts *iter)
{
	if (!iter)
		return ;
	if (iter->next)
		parse_opts(d, iter->next);
	if (iter->opt)
	{
		if (!d->s && !d->p && iter->opt == 'p' && d->arg_ind++)
			d->p = true;
		else if (!d->s && !d->q && iter->opt == 'q' && d->arg_ind++)
			d->q = true;
		else if (!d->s && !d->r && iter->opt == 'r' && d->arg_ind++)
			d->r = true;
		else if (!d->s && iter->opt == 's'&& (d->arg_ind += 2))
		{
			if (iter->arg == NULL)
				ft_ssl_md_error_no_string(d);
			d->arg_str = iter->arg;
			d->s = true;
		}
	}
}

static t_ft_ssl_md_data	*init()
{
	t_ft_ssl_md_data	*ret;

	if (!(ret = (t_ft_ssl_md_data *)ft_memalloc(sizeof(t_ft_ssl_md_data))))
		return (NULL);
	ret->p = false;
	ret->q = false;
	ret->r = false;
	ret->s = false;
	ret->f = false;
	ret->arg_ind = 1;
	ret->opts = NULL;
	ret->inputs = NULL;
	return (ret);
}

static void				get_digests(t_ft_ssl_md_data *d, t_ft_ssl_input *input,
							t_ft_ssl_md_fnc md)
{
	if (!input)
		return ;
	if (input->next)
		get_digests(d, input->next, md);
	if (input->input != NULL)
		input->output = md((t_byte *)input->input, input->input_len);
	print_digest(d, input);
}

t_ft_ssl_md_data		*ft_ssl_md(int argc, char **argv,
							t_ft_ssl_md_fnc md)
{
	int					i;
	t_ft_ssl_md_data	*d;

	if ((d = init()) == NULL)
		ft_error_unknown_free(FT_ERROR_UNKNOWN,
			(t_free_fnc)ft_ssl_md_free_data, d);
	d->name = ft_strdup(argv[0]);
	d->opts = ft_getopts(argc, argv, "pqrs;");
	parse_opts(d, d->opts);
	if (argv[d->arg_ind])
		d->f = true;
	if ((!d->s && !d->f) || d->p)
		ft_ssl_md_read_stdin(d);
	if (d->s)
		ft_ssl_md_read_string(d);
	if (d->f)
	{
		i = d->arg_ind;
		while (i < argc)
			ft_ssl_md_read_file(d, argv[i++]);
	}
	get_digests(d, d->inputs, md);
	ft_ssl_md_free_data(d);
	return (d);
}
