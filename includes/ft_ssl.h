#ifndef FT_SSL_H
#define FT_SSL_H

#include "sha256.h"
#include "md5.h"
#define SSL_BUFF_SIZE 16

typedef char  *(*t_ft_ssl_fnc)(t_byte *message, size_t length);

typedef struct      s_ft_ssl_data
{
    char    *input;
    size_t  input_length;
}                   t_ft_ssl_data;

typedef struct      s_ft_ssl_prg
{
    char            *type;
    t_ft_ssl_fnc    ssl_fnc;
}                   t_ft_ssl_prg;

static const t_ft_ssl_prg            g_ft_ssl_program_list[2] = {
    {"md5", &ft_md5},
    {"sha256", &ft_sha256}
};

char *ssl_parser(int argc, char **argv);






#endif
