#include "ft_ssl.h"
#include "libft.h"
#include <stdio.h>



void		display_usage(char *name)
{
    ft_putstr("usage: ");
    ft_putstr(name);
    ft_putendl(" message");
}



char *ssl_parser(int argc, char **argv)
{
    int             i;
    t_ft_ssl_data   *d;

    i = 0;
    d = init();

    if (argc == 2)
        ft_read_stdin(d);
    else
    {
        ft_read_file(d, argv[2]);
    }
    while (g_ft_ssl_program_list[i].type != NULL)
    {
        if (!(ft_strcmp(g_ft_ssl_program_list[i].type, ssl_fnc)))
            return (g_ft_ssl_program_list[i].ssl_fnc((t_byte *)d->msg, d->msg_len));
        i++;
    }
    display_usage("You failed");
    return (NULL);
}
