#include "minishell.h"

// добавить расшифровку по $ в имени файла

int	ms_error(int error, char *str)
{
	if (error == ERR_CMD)
		printf("Mimishell: %s: command not found\n", str);
	else if (error == ERR_TOKEN && (str[0] == 34 || str[0] == 39))
		printf("Mimishell: Unexpected EOF while looking for matching '%s' \n",
			str);
	else if (error == ERR_TOKEN)
		printf("Mimishell: Syntax error near unexpected token '%s' \n", str);
	else if (error == ERR_Q_MARK)
		write(2, "Mimisell: Skipped quotation_marks\n", 35);
	else if (error == ERR_NUM_ONE && str[0] == '!')
		printf("Mimishell: %s: event not found\n", str);
	else if (error == ERR_NUM_ONE)
		printf("Mimishell: export: '%s': not a valid identifier\n", str);
	return (-1);
}

int	ms_separator(t_data *data, char *line)
{
	int	i;

	i = 0;
	ms_count_and_record_cmd(data, line);
	if (data->num_error != 0)
		return (-1);
	while (i < data->num_cmd)
	{
		if (data->num_error == 0 && data->empty_str == NO)
			ms_found_redirect(&data->cmd[i], data);
		if (data->num_error == 0 && data->empty_str == NO
			&& data->cmd[i].str != NULL)
			ms_count_arg_divided_qm(&data->cmd[i], data);
		if (data->num_error == 0 && data->empty_str == NO
			&& data->cmd[i].str != NULL)
			ms_create_struct_without_qm(&data->cmd[i]);
		if (data->num_error == 0 && data->empty_str == NO
			&& data->cmd[i].str != NULL)
			ms_found_env_variable(data, &data->cmd[i]);
		i++;
		//printf ("i_sep = %d\n", i);
	}
	i = 0;
	return (0);
}

void	ms_init_data(t_data *data, char **env, int first)
{
	if (first == YES)
	{
		data->flag_old = 1;
		data->prev_dir = NULL; // for ft_cd.c
		data->cur_dir = getcwd(NULL, 0);
		data->num_prev_error = 0;
		data->num_error = 0;
		data->num_tmp_var = 0;
		ms_init_env(data, env);
		data->name_file = NO;
	}
	data->num_prev_error = data->num_error;
	data->num_error = 0;
	data->empty_str = NO;
	data->home_dir = getenv("HOME");
	data->build_in = YES;
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*line;
  
	if (argc != 1 || argv == NULL || env == NULL)
	{
		printf("Mimishell: this programm complies without arguments\n");
		exit(127);
	}
	ms_init_data(&data, env, YES);
	while (1)
	{
		ms_get_signal();
		ms_init_data(&data, env, NO);
		line = readline("\033[1;36mMiMiShell > \033[0m");
		ms_signal_ctrl_d(&data, line);
		if (line != 0)
		ms_separator(&data, line);
		ms_record_array(&data); // dlana add ms_record_array.c
		ms_execution(&data);
		//ms_execution(&data, data.cmd, env);
		if (data.empty_str == NO)
			add_history(line);
		ms_free_str(&line);
		// ms_free_cycle(&data, &line);
	}
	//ms_free_all(&data);
	// free (data->prev_dir) ???? // obeedril for ms_cd.c
	// free (data->cur_dir) ???? // obeedril for ms_cd.c

	// free data->cmd[n].way_cmd (check_first_arg.c)
}
