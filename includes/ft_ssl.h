#ifndef FT_SSL_H
#define FT_SSL_H

#include "sha256.h"
#include "md5.h"
#define SSL_BUFF_SIZE 16

typedef char    *(*t_ft_ssl_fnc)(t_byte *message, size_t length);

typedef struct  s_ft_ssl_prg
{
    char            *type;
    t_ft_ssl_fnc    ssl_fnc;
}               t_ft_ssl_prg;

typedef struct  s_ft_ssl_input
{
    char    *msg;
    size_t  msg_len;
    char    *digest;
}               t_ft_ssl_input;

typedef struct  s_ft_ssl_data
{
    t_bool          p;
    t_bool          r;
    t_bool          q;
    t_bool          s;
    t_bool          f;
    char            *arg_iter;
    size_t          arg_ind;
    size_t          input_count;
    t_list          *inputs;
    t_ft_ssl_prg    ssl_prg;
}               t_ft_ssl_data;

static const t_ft_ssl_prg            g_ft_ssl_program_list[3] = {
    {"md5", &ft_md5},
    {"sha256", &ft_sha256},
    {NULL, NULL}
};

void    ft_ssl_read_stdin(t_ft_ssl_data *d);
void    ft_ssl_read_string(t_ft_ssl_data *d);
void    ft_ssl_read_file(t_ft_ssl_data *d, const char *path);
#endif
