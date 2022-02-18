#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

//int global_err;

typedef enum e_value
{
	NO,
	YES,
	REDIR_R, // <
	REDIR_W, // >
	REDIR_W_ADD, // >>
	HEREDOC, // <<
	REDIR_ROMB, // <>
	ERR_PIPE,
	ERR_MEMORY,
	ERR_Q_MARK,
	DOUBLE_Q_MARK = 34,
	ONE_Q_MARK = 39,
	ERR_CMD = 127,
	ERR_TOKEN = 258,
}				t_value;

typedef struct s_arg
{
	char			*str;
	int				q_m;
	int				space;
	int				redir;

}				t_arg;

typedef struct s_cmd
{
	char	*str;
	t_arg	*arg; // не использовать
	char 	**array_arg;
	int		*redir; // = enum
	char	**file; // имя файла
	int		num_arg; // не использовать
	int		num_array_arg;
}				t_cmd;

typedef struct s_tmp
{
	//int		size_k;
	//int		size_v;
	int		size_str;
	int		size_cut;
	int		count;
}				t_tmp;

typedef struct s_data
{
	t_cmd	*cmd;
	t_tmp	tmp;
	int		num_cmd;
	int		num_error;
	int		num_prev_error;
	char    **our_env; // dlana
	char	*prev_dir; // obeedril for ms_cd.c
	char	*cur_dir; // obeedril for ms_cd.c
	char	*home_dir; // obeedril for ms_cd.c
}				t_data;

int ms_count_and_record_cmd(t_data *data, char *line);

void	ms_free_str(char **tmp_str);
void	ms_malloc_str(char **name, int size);
void	ms_malloc_arg(t_arg **arg, int size);
void	ms_malloc_cmd(t_cmd **cmd, int size);

int		ms_our_cmd(t_data *data, char **env);
int		ms_found_env_variable(int err, t_cmd *cmd);
void	ms_replase_key_to_value(char **str, char *key, const char *value, int start);
void	ms_record_char(char **result, const char *str, int *r, int *s);
int		ms_error(int *error, char *str);
void	check_first_arg(t_data *data); // obeedril added for check a first agr
void	ms_cd(char *arg_way, t_data *data, int i); // obeedril for ms_cd.c
void	ms_pwd(void); // obeedril for ms_pwd.c
void	ms_exit(t_data *data, int num_array_arg, char *exit_arg); // obeedril for ms_exit.c
int		ms_record_array(t_data *data);
int		ms_get_signal(void); // obeedril for signal
void	rl_replace_line (const char *text, int clear_undo); // obeedril for readline
void    ms_malloc_array(char ***array, int size);
int		ms_found_redirect(t_cmd *cmd, t_data *data);
void	ms_record_str(char **file, char *str, int start, int size_str);

#endif
