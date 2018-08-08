#include "ft_ssl.h"
#include "libft.h"
#include "gnl.h"
#include <stdio.h>

void		display_usage(char *name)
{
    ft_putstr("usage: ");
    ft_putstr(name);
    ft_putendl(" message");
}

void    ft_read_stdin(t_ft_ssl_data *d)
{
    int     check;
    char    buf[SSL_BUFF_SIZE];
    char    *stdin_str;

    d->input_length = 0;
    stdin_str = ft_strnew(0);
    while((check = read(0, &buf, SSL_BUFF_SIZE)) > 0)
    {
        ft_strcat(stdin_str, buf);
		stdin_str[check] = 0;
        d->input_length += check;
    }
    if (check < 0)
        d->input = NULL;
    d->input = stdin_str;
}

char *ssl_parser(int argc, char **argv)
{
    int             i;
    char            *ssl_fnc;
    t_ft_ssl_data   *d;

    i = 0;
    ssl_fnc = argv[1];
    if (!(d = (t_ft_ssl_data *)ft_memalloc(sizeof(t_ft_ssl_data))))
        return (NULL);
    if (argc < 2 || argc > 3)
    {
        display_usage("Should try to open from stdin?");
        return (NULL);
    }
    if (argc == 2)
        ft_read_stdin(d);
    else
    {
        d->input = ft_strdup(argv[2]);
        d->input_length = ft_strlen(argv[2]);
    }
    while (i < 2)
    {
        ssl_fnc = argv[1];
        if (!(ft_strcmp(g_ft_ssl_program_list[i].type, ssl_fnc)))
            return (g_ft_ssl_program_list[i].ssl_fnc((t_byte *)d->input, d->input_length));
        i++;
    }
    display_usage("You failed");
    return (NULL);
}
