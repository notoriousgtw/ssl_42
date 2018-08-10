#ifndef FT_SSL_H
#define FT_SSL_H

#include "sha256.h"
#include "md5.h"
#define SSL_BUFF_SIZE 16
#define INPUT_STDIN 0
#define INPUT_STRING 1
#define INPUT_FILE 2

typedef char    *(*t_ft_ssl_fnc)(t_byte *message, size_t length);

typedef struct  s_ft_ssl_prg
{
    char            *name;
    t_ft_ssl_fnc    ssl_fnc;
    size_t          digest_len;
}               t_ft_ssl_prg;

typedef struct  s_ft_ssl_input
{
    int                     input_type;
    char                    *filename;
    char                    *msg;
    size_t                  msg_len;
    char                    *digest;
    struct s_ft_ssl_input   *next;
}               t_ft_ssl_input;

typedef struct  s_ft_ssl_data
{
    t_bool          p;
    t_bool          r;
    t_bool          q;
    t_bool          s;
    t_bool          f;
    char            *arg_str;
    size_t          arg_ind;
    t_ft_ssl_input  *inputs;
    t_ft_ssl_prg    *ssl_prg;
}               t_ft_ssl_data;

static const t_ft_ssl_prg            g_ft_ssl_program_list[3] = {
    {"md5", &ft_md5, 32},
    {"sha256", &ft_sha256, 64},
    {NULL, NULL, 0}
};

void    ft_ssl_read_stdin(t_ft_ssl_data *d);
void    ft_ssl_read_string(t_ft_ssl_data *d);
void    ft_ssl_read_file(t_ft_ssl_data *d, char *path);

void	print_digest(t_ft_ssl_data *d, t_ft_ssl_input *input);

void    ft_ssl_error_prg(char *prg);
void    ft_ssl_error_nostring(t_ft_ssl_data *d);

void    ft_ssl_free_data(t_ft_ssl_data *d);
#endif
