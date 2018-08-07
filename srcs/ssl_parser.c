#include "ft_ssl.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>

void		display_usage(char *name)
{
    ft_putstr("usage: ");
    ft_putstr(name);
    ft_putendl(" message");
}

char *ft_read_stdin(void)
{
    char *stdin_str[BUFF_SIZE + 1];
    int ret;

    ret = 1;
    while(ret > 0)
    {
        ret = read(0, stdin_str, BUFF_SIZE);
        stdin_str[ret] = '\0';
    }
    return (stdin_str);
}

char *ssl_parser(int argc, char **argv)
{
    int i;
    char *input;

    i = 0;
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
        if (!(ft_strcmp(g_ft_ssl_program_list[i].type, argv[1])))
            return (g_ft_ssl_program_list[i].ssl_fnc(input));
        i++;
    }
    display_usage("You failed");
    return (NULL);
}