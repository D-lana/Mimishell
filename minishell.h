#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include <fcntl.h>

typedef enum e_value
{
	NO,
	YES,
	YES_AFTER_PARSER,
	REDIR_R, // <
	REDIR_W, // >
	REDIR_W_ADD, // >>
	HEREDOC, // <<
	REDIR_ROMB, // <>
	ERR_PIPE,
	ERR_MEMORY,
	ERR_Q_MARK,
	ADD_TO_OLD,
	ADD_NEW,
	DOUBLE_Q_MARK = 34,
	ONE_Q_MARK = 39,
	ERR_CMD = 127,
	ERR_TOKEN = 258,
	ERR_EXPORT = 1,
}				t_value;

typedef struct s_arg
{
	char			*str;
	int				q_m;
	int				space;
	int				redir;
	int				empty_key;

}				t_arg;

typedef struct s_cmd
{
	char	*str;
	t_arg	*arg; // не использовать
	char 	**array_arg;
	int		*redir; // = enum
	char	**file; // имя файла
	int		fd[2];
	int		num_arg; // не использовать
	int		num_array_arg;
	char	*way_cmd;
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
	int		num_env;
	char	**our_env; // dlana
	char	**tmp_var; // dlana
	int		num_tmp_var;
	int		only_var;
	char	*prev_dir; // obeedril for ms_cd.c
	char	*cur_dir; // obeedril for ms_cd.c
	char	*home_dir; // obeedril for ms_cd.c
	int		empty_str;
	int		count_redir;
}				t_data;

int		ms_count_and_record_cmd(t_data *data, char *line);
int		ms_found_redirect(t_cmd *cmd, t_data *data);
int		ms_count_arg_divided_qm(t_cmd *cmd, t_data *data); // dlana
void	ms_create_struct_without_qm(t_cmd *cmd); // dlana
void	ms_switch_qm(char *s, int i, int *qm_o, int *qm_d); // dlana
int		ms_found_env_variable(int err, t_cmd *cmd);
void	ms_replase_key_to_value(char **str, int key, char *value, int start);
void	ms_record_array(t_data *data);
void	ms_init_env(t_data *data, char **env); // dlana

int		ms_add_env_variable(t_data *data, int i_cmd); // dlana
void	ms_found_variable(t_data *data);
int		ms_valid_export(char *var);
int		ms_cut_array_arg(char ***arr, int *count_arr, int y);

int		ms_our_cmd(t_data *data, int i);

void	ms_cd(char *arg_way, t_data *data, int i); // obeedril for ms_cd.c
void	ms_pwd(void); // obeedril for ms_pwd.c
void	ms_exit(t_data *data, int num_array_arg, char *exit_arg); // obeedril for ms_exit.c
void	ms_export(t_data *data, int i); // dlana
int		ms_unset(t_data *data, int i_cmd); // dlana
void	ms_execve(t_cmd *cmd, t_data *data);

int		ms_get_signal(void); // obeedril for signal
void	ms_signal_ctrl_d(char *line); // dlana relocate

void	ms_record_str(char **file, char *str, int start, int size_str); // dlana
void	ms_record_char(char **result, char *str, int *r, int *s);

int		ms_error(int *error, char *str);
void	ms_check_first_arg(t_data *data); // obeedril added for check a first agr

void	ms_free_str(char **str);
void	ms_free_arr(char ***arr);
void	ms_free_int_arr(int **int_arr);

void	ms_malloc_str(char **name, int size);
void	ms_malloc_arg(t_arg **arg, int size);
void	ms_malloc_cmd(t_cmd **cmd, int size);
void	ms_malloc_array(char ***array, int size);
int		*ms_malloc_arr_int(int **arr_int, int size);

void	rl_replace_line (const char *text, int clear_undo); // obeedril for readline

void	ms_execution(t_data *data, t_cmd **cmd, char **env); //obeedril added



#endif
