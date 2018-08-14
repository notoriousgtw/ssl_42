/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 21:12:33 by gwood             #+#    #+#             */
/*   Updated: 2018/08/13 19:40:16 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"

static void				parse_args(t_ft_ssl_data *d, int argc, char **argv)
{
	int			i;
	uint32_t	cnt;

	cnt = 0;
	i = 1;
	while (i++ < argc)
	{
		if (!d->s && !d->p && argv[i] && ft_strcmp("-p", argv[i]) == 0 && ++cnt)
			d->p = true;
		else if (!d->s && !d->q && argv[i] && ft_strcmp("-q", argv[i]) == 0 && ++cnt)
			d->q = true;
		else if (!d->s && !d->r && argv[i] && ft_strcmp("-r", argv[i]) == 0 && ++cnt)
			d->r = true;
		else if (!d->s && argv[i] && ft_strcmp("-s", argv[i]) == 0)
		{
			if (++i >= argc)
				ft_ssl_error_no_string(d);
			d->arg_str = argv[i];
			d->s = true;
			cnt += 2;
		}
		else if (argv[i] && (d->f = true))
			break ;
	}
	d->arg_ind = 2 + cnt;
}

static t_ft_ssl_data	*init(char *ssl_cmd)
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
	while (g_ft_ssl_program_list[i].name != NULL)
	{
		if (!(ft_strcmp(g_ft_ssl_program_list[i].name, ssl_cmd)))
			ret->ssl_prg = &(((t_ft_ssl_prg *)g_ft_ssl_program_list)[i]);
		i++;
	}
	if (ret->ssl_prg == NULL)
		ft_ssl_error_invalid_command(ret, ssl_cmd);
	return (ret);
}

static void				get_digests(t_ft_ssl_data *d, t_ft_ssl_input *input,
	t_ft_ssl_fnc get_digest)
{
	if (!input)
		return ;
	if (input->next)
		get_digests(d, input->next, get_digest);
	if (input->msg != NULL)
		input->digest = get_digest((t_byte *)input->msg, input->msg_len);
	print_digest(d, input);
}

int						main(int argc, char **argv)
{
	int				i;
	t_ft_ssl_data	*d;

	if (argc > 1 && argv[1] != NULL)
	{
		if ((d = init(argv[1])) == NULL)
			ft_error_unknown_free(FT_ERROR_UNKNOWN,
				(t_free_fnc)ft_ssl_free_data, d);
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
		get_digests(d, d->inputs, d->ssl_prg->ssl_fnc);
		ft_ssl_free_data(d);
	}
	else
		ft_putendl("usage: ft_ssl command [command opts] [command args]");
}
