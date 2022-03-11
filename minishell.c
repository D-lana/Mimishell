#include "minishell.h"

// добавить расшифровку по $ в имени файла +
// > $PWD -
//bash: /Users/dlana/git_mimi: Is a directory -

int	ms_separator(t_data *data, char *line)
{
	int	i;

	i = 0;
	ms_count_and_record_cmd(data, line);
	if (data->num_error != 0 || data->empty_str == YES)
		return (-1);
	while (i < data->num_cmd)
	{
		if (data->num_error == 0)
			ms_found_redirect(&data->cmd[i], data);
		if (data->num_error == 0 && data->cmd[i].str != NULL)
			ms_count_arg_divided_qm(&data->cmd[i], data);
		if (data->num_error == 0 && data->cmd[i].str != NULL)
			ms_create_struct_without_qm(&data->cmd[i]);
		if (data->num_error == 0 && data->cmd[i].str != NULL)
			ms_found_env_variable(data, &data->cmd[i]);
		i++;
	}
	i = 0;
	return (0);
}

void	ms_init_data(t_data *data, char ***env, int first)
{
	if (first == YES)
	{
		data->flag_old = 1;
		data->prev_dir = NULL;
		data->cur_dir = getcwd(NULL, 0);
		data->num_prev_error = 0;
		data->num_error = 0;
		data->num_tmp_var = 0;
		data->tmp_var = NULL;
		
		ms_init_env(data, env);
		data->name_file = NO;
	}
	data->num_prev_error = data->num_error;
	data->num_error = 0;
	data->empty_str = NO;
	data->home_dir = getenv("HOME");
	data->build_in = YES;
	data->num_cmd = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*line;
  
	ms_err_argc_argv(argc, argv, env);
	ms_init_data(&data, &env, YES);
	while (1)
	{
		ms_get_signal();
		ms_init_data(&data, &env, NO);
		line = readline("\033[1;35mMiMiShell > \033[0m");
		ms_signal_ctrl_d(&data, &line);
		ms_separator(&data, line);
		if (data.empty_str == NO)
		{
			ms_record_array(&data);
			ms_execution(&data);
			add_history(line);
			ms_free_cycle(&data, &line);
		}
	}
	// ms_free_all(&data);
	// free data->cmd[n].way_cmd (check_first_arg.c)
}
