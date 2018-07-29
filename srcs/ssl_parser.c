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

char *ft_read_stdin(void)
{
    char *stdin_str;
    int ret;

    ret = 69;
    
    ft_gnl(1, &stdin_str);
    printf("%s", stdin_str);
    return (stdin_str);
}

char *ssl_parser(int argc, char **argv)
{
    int i;
    char *input;
    char *ssl_fnc;

    i = 0;
    ssl_fnc = argv[1];
    if (argc < 2 || argc > 3)
    {
        display_usage("Should try to open from stdin?");
        return (NULL);
    }
    if (argc == 2)
        input = ft_read_stdin();
    else
        input = argv[2];
    while (i < 2)
    {
        ssl_fnc = argv[1];
        if (!(ft_strcmp(g_ft_ssl_program_list[i].type, ssl_fnc)))
            return (g_ft_ssl_program_list[i].ssl_fnc(input));
        i++;
    }
    display_usage("You failed");
    return (NULL);
}