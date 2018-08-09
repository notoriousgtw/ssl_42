/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 21:12:33 by gwood             #+#    #+#             */
/*   Updated: 2018/08/08 17:13:50 by gwood            ###   ########.fr       */
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
        if (ft_strcmp("-p", argv[i]) == 0 && ++cnt)
            d->p = true;
        else if (ft_strcmp("-q", argv[i]) == 0 && ++cnt)
            d->q = true;
        else if (ft_strcmp("-r", argv[i]) == 0 && ++cnt)
            d->r = true;
        else if (ft_strcmp("-s", argv[i]) == 0)
		{
			if ((i + 1) == argc || argv[i + 1] == NULL)
				ft_error("please provide a string");
            d->s = true;
			cnt += 2;
			break;
		}
		else
		{
			d->f = true;
			cnt++;
			break;
		}

		i++;
    }
	d->arg_iter = argv[1 + cnt];
	d->arg_ind = 1 + cnt;
}

t_ft_ssl_data   *init(char *ssl_fnc)
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
	ret->arg_iter = NULL;
	ret->arg_ind = 0;
	ret->input_count = 0;
	ret->inputs = NULL;
	i = 0;
    while (g_ft_ssl_program_list[i].type != NULL)
    {
        if (!(ft_strcmp(g_ft_ssl_program_list[i].type, ssl_fnc)))
            ret->ssl_prg = g_ft_ssl_program_list[i];
        i++;
    }
	return (ret);
}

void	print_digest(t_ft_ssl_input *input, t_ft_ssl_data *d)
{
	ft_putendl(d->ssl_prg.ssl_fnc((t_byte *)input->msg, input->msg_len));
}

void	msg_iter(t_list *elem, void *data)
{
	t_ft_ssl_data	*d;
	t_ft_ssl_input	*cast;

	d = (t_ft_ssl_data *)data;
	cast = (t_ft_ssl_input *)elem->content;
	print_digest(cast, d);
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
			while (i++ < argc)
				ft_ssl_read_file(d, d->arg_iter);
			ft_lstiter_data(d->inputs, msg_iter, d);
		}
	}
}
