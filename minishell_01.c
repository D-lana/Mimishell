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

int	ms_cut_quotation_marks(char *str, t_arg *arg, int i)
{
	int c;
	char q_m;

	c = 0;
	q_m = str[i];
	i++;
	arg->q_m = (int)q_m;
	while (str[i] != q_m && str[i] != '\0') 
	{
		c++;
		i++;
	}
	ms_malloc_str(&arg->str, c);
	i = i - c;
	c = 0;
	while (str[i] != q_m && str[i] != '\0')
		ms_record_char(&arg->str, str, &c, &i);
	if (str[i] == q_m)
	{
		i++;
		if (str[i] == ' ')
			arg->space = YES;
	}
	arg->str[c] = '\0';
	return(i); //// +1
}

int	ms_record_args_without_qm(char *str, t_arg *arg, int i)
{
	int c = 0;
	arg->q_m = NO;
	while (str[i] != 39 && str[i] != 34 && str[i] != '\0' && str[i] != ' ')
	{
		c++;
		i++;
	}
	ms_malloc_str(&arg->str, c);
	i = i - c;
	c = 0;
	while (str[i] != 39 && str[i] != 34 && str[i] != '\0' && str[i] != ' ')
		ms_record_char(&arg->str, str, &c, &i); // printf("%c", arg->str[c] = str[i]);
	arg->str[c] = '\0';
	if (str[i] == ' ')
		arg->space = YES;
	return (i);
}

void	ms_create_struct_without_qm(t_cmd *cmd) 
{
	int	i;
	int num_arg;

	i = 0;
	num_arg = 0;
	ms_malloc_arg(&cmd->arg, cmd->num_arg);
	while (cmd->str[i] != '\0')
	{
		if (cmd->str[i] == 34 || cmd->str[i] == 39)
		{
			cmd->arg[num_arg].space = NO;
			i = ms_cut_quotation_marks(cmd->str, &cmd->arg[num_arg], i);
			num_arg++;
		}
		else
		{
			while (cmd->str[i] != 34 && cmd->str[i] != 39 && cmd->str[i] != '\0')
			{
				if (cmd->str[i] != ' ')
				{
					cmd->arg[num_arg].space = NO;
					i = ms_record_args_without_qm(cmd->str, &cmd->arg[num_arg], i);
					num_arg++; //printf("stroka = %s", cmd->arg[num_arg].str);
				}
				else 
					i++;
			}
		}
	}
}

int ms_check_quotation_marks(t_cmd *cmd, int i, t_data *data)
{
	char q_m;

	q_m = cmd->str[i];
	i++;//printf("%c", cmd->str[i]);
	while (cmd->str[i] != q_m && cmd->str[i] != '\0')
		i++;
	if (cmd->str[i] == q_m)
		cmd->num_arg++;
	else
	{
		data->num_error = ERR_Q_MARK;
		return((ms_error(&data->num_error, NULL)));
	}
	return (i + 1);
}

int ms_count_args_without_qm(t_cmd *cmd, int i)
{
	if (cmd->str[i] == ' ')
	{
		while (cmd->str[i] == ' ')
			i++;
	}
	if (cmd->str[i] != 39 && cmd->str[i] != 34 && cmd->str[i] != '\0')
		cmd->num_arg++;
	while (cmd->str[i] != 39 && cmd->str[i] != 34 && cmd->str[i] != '\0')
	{
		if (cmd->str[i] == ' ')
		{
			while (cmd->str[i] == ' ' && cmd->str[i] != '\0')///////////////////////
				i++;
			if (cmd->str[i] != 39 && cmd->str[i] != 34 && cmd->str[i] != '\0')
				cmd->num_arg++;
		}
		else
			i++; //printf("%c", cmd->str[i]);
	}
	return(i);
}

int ms_count_arg_divided_qm(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	cmd->num_arg = 0;
	while (cmd->str[i] != '\0')
	{
		if (cmd->str[i] == 34 || cmd->str[i] == 39)
			i = ms_check_quotation_marks(cmd, i, data);
		else
			i = ms_count_args_without_qm(cmd, i);
		if (i == -1)
			return (-1);
	}
	return (0);
}

int ms_separator(t_data *data, char *line)
{
	int	i;

	i = 0;
	ms_count_and_record_cmd(data, line);
	if (data->num_error != 0)
		return(-1);
	while (i < data->num_cmd)
	{
		ms_count_arg_divided_qm(&data->cmd[i], data);
		if(data->num_error == 0)
			ms_create_struct_without_qm(&data->cmd[i]);
		if(data->num_error == 0)
			ms_found_env_variable(data->num_prev_error, &data->cmd[i]);
		printf("%d\n", data->cmd[i].num_arg);
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
				printf("%s", data->cmd[i].arg[j].str);
				if(data->cmd[i].arg[j].space == YES)
					printf(" ");
				j++;
			}
			i++;
			j = 0;
		}
		printf("\n");////////////
	} 
	return (0);
}

void ms_count_arg_for_array(t_cmd *cmd)
{
	int i;

	i = 0;
	cmd->num_array_arg = 1;
	while (i < cmd->num_arg)
	{
		if (cmd->arg[i].space == YES)
			cmd->num_array_arg++;
		i++;
	}
}

int ms_connect_arg_for_array(t_cmd *cmd)
{
	int i;
	int x;
	int size_str;

	i = 0;
	x = 0;
	size_str = 0;
	cmd->array_arg = (char **)malloc(sizeof(char *) * (cmd->num_array_arg + 1));
	while (i < cmd->num_arg && cmd->arg[i].space != YES)
	{
		while (cmd->arg[i].str[x] != '\0')
		{
			x++;
		}
		i++;
		size_str += x;
		x = 0;
	}
	return(0);
}

int ms_record_massiv(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_cmd)
	{
		ms_count_arg_for_array(&data->cmd[i]);
		ms_connect_arg_for_array(&data->cmd[i]);
		//data->cmd[i].array_arg
		i++;
	}
	return(0);
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
		data.num_error = 0;
		data.home_dir = getenv("HOME"); // obeedril for ft_cd.c
		line = readline("\033[1;36m MiMiShell > \033[0m");
		if (line == NULL)
		{
			write (1, "\033[1AMiMishell exit\n", 20);
			exit(EXIT_SUCCESS);
		}
		ms_separator(&data, line);
		ms_record_massiv(&data);
		//check_first_arg(&data);
		ms_our_cmd(&data, env);
		data.num_prev_error = data.num_error;
		add_history(line);
		if (line)
			free(line);
	}
	// free (data->prev_dir) ???? // obeedril for ms_cd.c
}