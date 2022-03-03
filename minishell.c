
#include "minishell.h"

// добавить расшифровку по $ в имени файла

int	ms_error(int error, char *str)
{
	if (error == ERR_CMD)
		printf("Mimishell: %s: command not found\n", str);
	else if (error == ERR_TOKEN && (str[0] == 34 || str[0] == 39))
		printf("Mimishell: Unexpected EOF while looking for matching '%s' \n", str);
	else if (error == ERR_TOKEN)
		printf("Mimishell: Syntax error near unexpected token '%s' \n", str);
	else if (error == ERR_Q_MARK)
		write(2, "Mimisell: Skipped quotation_marks\n", 35);
	else if (error == ERR_EXPORT && str[0] == '!')
		printf("Mimishell: %s: event not found\n", str);
	else if (error == ERR_EXPORT)
		printf("Mimishell: export: '%s': not a valid identifier\n", str);
	return(-1);
}

void ms_record_char(char **result, char *str, int *r, int *s)
{
	(*result)[(*r)] = str[(*s)];
	(*r)++;
	(*s)++;
}

void ms_record_str(char **file, char *str, int start, int size_str)
{
	int i;

	i = 0;
	while(i < size_str)
	{
		(*file)[i] = str[start + i];
		i++;
	}
	(*file)[i] = '\0';
}

int ms_separator(t_data *data, char *line)
{
	int i;
	i = 0;
	ms_count_and_record_cmd(data, line);
	if (data->num_error != 0)
		return(-1);
	while (i < data->num_cmd)
	{
		if(data->num_error == 0 && data->empty_str == NO)
			ms_found_redirect(&data->cmd[i], data);
		if(data->num_error == 0 && data->empty_str == NO && data->cmd[i].str != NULL)
			ms_count_arg_divided_qm(&data->cmd[i], data);
		if(data->num_error == 0 && data->empty_str == NO && data->cmd[i].str != NULL)
			ms_create_struct_without_qm(&data->cmd[i]);
		if(data->num_error == 0 && data->empty_str == NO && data->cmd[i].str != NULL)
			ms_found_env_variable(data->num_prev_error, &data->cmd[i]);
		i++;
	}
	i = 0;
	return (0);
}

void ms_init_data(t_data *data, char **env, int first)
{
	if (first == YES)
	{
		data->flag_old = 1;
		data->prev_dir = NULL; // for ft_cd.c
		data->num_prev_error = 0;
		data->num_tmp_var = 0;
		ms_init_env(data, env);
	}
	data->num_prev_error = data->num_error;
	data->num_error = 0;
	data->empty_str = NO;
	data->home_dir = getenv("HOME"); // obeedril for ft_cd.c
}

void ms_free_all(t_data *data)
{
	ms_free_arr(&data->our_env);
	ms_free_arr(&data->tmp_var);
}


void ms_free_cycle(t_data *data, char **line)
{
	int i;

	i = 0;
	ms_free_str(line);
	while (data->num_cmd > 0)
	{
		while (i < data->cmd[data->num_cmd].num_arg)
		{
			ms_free_str(&data->cmd[data->num_cmd].arg[i].str);
			data->cmd[data->num_cmd].arg[i].str = NULL;
			i++;
		}
		if (data->cmd[data->num_cmd].arg)
			free(data->cmd[data->num_cmd].arg);
		if (data->cmd[data->num_cmd].num_array_arg > 0)
			ms_free_arr(&data->cmd[data->num_cmd].array_arg);
		if (data->cmd->count_redir > 0)
		{
			ms_free_int_arr(&data->cmd->redir);
			ms_free_arr(&data->cmd[data->num_cmd].file);
		}
		data->num_cmd--;
	}
	free(data->cmd);
	data->cmd = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_data data;
	char *line;

	if (argc < 1 || argv == NULL || env == NULL)
		exit(127);
	ms_init_data(&data, env, YES);
	while (1)
	{
		ms_get_signal(); // obeedril for ms_get_signal.c
		ms_init_data(&data, env, NO);
		line = readline("\033[1;36mMiMiShell > \033[0m");
		ms_signal_ctrl_d(&data, line);
		if (line != 0)
			ms_separator(&data, line);
		ms_record_array(&data); // dlana add ms_record_array.c
		//ms_exe(&data);
		ms_execution(&data);
		if (data.empty_str == NO)
			add_history(line);
		ms_free_cycle(&data, &line);
	}
	ms_free_all(&data);
	// free (data->prev_dir) ???? // obeedril for ms_cd.c
}