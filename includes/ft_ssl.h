#ifndef FT_SSL_H
#define FT_SSL_H

#include "sha256.h"
#include "md5.h"
#define SSL_BUFF_SIZE 16

typedef char  *(*t_ft_ssl_fnc)(t_byte *message, size_t length);

typedef char *(*t_ft_ssl_args)(t_ssl_args *args);

typedef struct s_ssl_args
{
    char        *input;
    char        *stdin_str;
    char        *flags
}               t_ssl_args;

typedef struct      s_ft_ssl_prg
{
    char            *type;
    t_ft_ssl_fnc    ssl_fnc;
}                   t_ft_ssl_prg;

static const t_ft_ssl_prg            g_ft_ssl_program_list[2] = {
    {"md5", &ft_md5},
    {"sha256", &ft_sha256}
};

static const t_ssl_args           g_ft_ssl_flags =
{
    {"p", &ft_ssl_echo_stdout},
    {"q", &ft_ssl_quiet_mode},
    {"r", &ft_ssl_rev_fmt},
    {"s", &ft_ssl_print_sum}
};

char *ft_ssl_echo_stdout(char *input);
char *ft_ssl_quiet_mode(char *input);
char *ft_ssl_rev_fmt(char *input);
char *ft_ssl_print_sum(char *input);

#endif
