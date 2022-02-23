
#include "minishell.h"

int	ms_error(int *error, char *str)
{
	if ((*error) == ERR_CMD)
		printf("Mimishell: %s: command not found\n", str);
	else if ((*error) == ERR_TOKEN && (str[0] == 34 || str[0] == 39))
		printf("Mimishell: Unexpected EOF while looking for matching '%s' \n", str);
	else if ((*error) == ERR_TOKEN)
		printf("Mimishell: Syntax error near unexpected token '%s' \n", str);
	else if ((*error) == ERR_Q_MARK)
		write(2, "Mimisell: Skipped quotation_marks\n", 35);
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
		if(data->num_error == 0 && data->empty_str == NO)
		{
			ms_count_arg_divided_qm(&data->cmd[i], data);
		}
		if(data->num_error == 0 && data->empty_str == NO)
			ms_create_struct_without_qm(&data->cmd[i]);
		if(data->num_error == 0 && data->empty_str == NO)
			ms_found_env_variable(data->num_prev_error, &data->cmd[i]);
		i++;
	}
	i = 0;
	// int j = 0;
	// if(data->num_error == 0 && data->empty_str == NO) ////////////// распечатка, убрать)
	// {
	//     while (i < data->num_cmd)
	//     {
		   
	// 	    while (j < data->cmd[i].num_arg)
	//         {
	// 			printf("%s", data->cmd[i].arg[j].str);
	//             if(data->cmd[i].arg[j].space == YES)
	//                printf(" ");
	//             j++;
	//         }
	//         i++;
	//         j = 0;
	//     }
	//   //  printf("\n");////////////
	// }
	return (0);
}

void ms_init_data(t_data *data)
{
	data->num_error = 0;
	data->empty_str = NO;
	data->home_dir = getenv("HOME"); // obeedril for ft_cd.c
}

int	main(int argc, char **argv, char **env)
{
	t_data data;
	char *line;

	data.prev_dir = NULL; // for ft_cd.c
	if (argc < 1 || argv == NULL || env == NULL)
		exit(1);
	data.num_prev_error = 0;
	ms_init_env(&data, env);
	while (1)
	{
		ms_get_signal(); // obeedril for ms_get_signal.c
		ms_init_data(&data);
		line = readline("\033[1;36mMiMiShell > \033[0m");
		ms_signal_ctrl_d(line);
		ms_separator(&data, line);
		ms_record_array(&data); // dlana add ms_record_array.c
		//ms_check_first_arg(&data); // obeedril add for check first argument
		//ms_execution(&data, &data.cmd, env);
		ms_our_cmd(&data);
		data.num_prev_error = data.num_error;
		add_history(line);
		ms_free_str(&line);
	}
	// free (data->prev_dir) ???? // obeedril for ms_cd.c
}