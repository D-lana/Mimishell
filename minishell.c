#include "minishell.h"


int	ms_error(int *error, char *str)
{
	if ((*error) == ERR_CMD)
		printf("Mimishell: %s: command not found\n", str);
	if ((*error) == ERR_TOKEN)
		printf("Mimishell: Syntax error near unexpected token '%s' \n", str);
	if ((*error) == ERR_Q_MARK)
		write(2, "Mimisell: Skipped quotation_marks\n", 35);
	return(-1);
}

void ms_record_char(char **result, const char *str, int *r, int *s)
{
	(*result)[(*r)] = str[(*s)];
	(*r)++;
	(*s)++;
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
        if(data->num_error == 0)
            ms_found_redirect(&data->cmd[i], data);
        if(data->num_error == 0)
            ms_count_arg_divided_qm(&data->cmd[i], data);
        if(data->num_error == 0)
            ms_create_struct_without_qm(&data->cmd[i]);
        if(data->num_error == 0)
            ms_found_env_variable(data->num_prev_error, &data->cmd[i]);
        //printf("%d\n", data->cmd[i].num_arg);
        i++;
    }
    i = 0;
    int j = 0;
    if(data->num_error == 0) ////////////// распечатка, убрать)
    {
        while (i < data->num_cmd)
        {
            while (j < data->cmd[i].num_arg)
            {
                //printf("%s", data->cmd[i].arg[j].str);
                if(data->cmd[i].arg[j].space == YES)
                   printf(" ");
                j++;
            }
            i++;
            j = 0;
        }
      //  printf("\n");////////////
    }
    return (0);
}


int	main(int argc, char **argv, char **env)
{
	int i;
	t_data data;
	char *line;

	data.prev_dir = NULL; // for ft_cd.c
	if (argc < 1 || argv == NULL)
		exit(1);
	i = 0;
	data.num_prev_error = 0;
	while (1)
	{
		ms_get_signal(); // obeedril for ms_get_signal.c
		data.num_error = 0;
		data.home_dir = getenv("HOME"); // obeedril for ft_cd.c
		line = readline("\033[1;36mMiMiShell > \033[0m");
		if (line == NULL)
		{
			printf("\033[1;36m\bMiMiShell >\033[0A"); 
			printf("\033[1;0m exit\n\033[0m");
			exit(EXIT_SUCCESS);
		}
		ms_separator(&data, line);
		ms_record_array(&data); // dlana add ms_record_array.c
		check_first_arg(&data); // obeedril add for check first argument
		ms_our_cmd(&data, env);
		data.num_prev_error = data.num_error;
		add_history(line);
		ms_free_str(&line);
	}
	// free (data->prev_dir) ???? // obeedril for ms_cd.c
}
