#include "minishell.h"

void	ms_record_array(t_data *data);
void	ms_count_arg_for_array(t_cmd *cmd);
void	ms_connect_arg_for_array(t_cmd *cmd);
int		ms_record_arg(t_cmd *cmd, char **str, int *i, int len);

void ms_printf_array(t_data *data)
{
	int	i;
	int y;

	i = 0;
	y = 0;
	while (y < data->num_cmd)
	{
		while (i < data->cmd->num_array_arg)
		{
			printf("%s ", data->cmd[y].array_arg[i]);
			i++;
		}
		printf("%s ", data->cmd[y].array_arg[i]);
		printf("%s ", data->cmd[y].array_arg[i + 1]);
		printf("%s ", data->cmd[y].array_arg[i + 2]);
		y++;
	}

	printf("\n");
}

void	ms_record_array(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_error != 0 || data->empty_str == YES)
		return ;
	while (i < data->num_cmd)
	{
		ms_count_arg_for_array(&data->cmd[i]);
		ms_connect_arg_for_array(&data->cmd[i]);
		i++;
	}
	ms_printf_array(data); ///// распечатка убрать
}

void	ms_count_arg_for_array(t_cmd *cmd)
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

void	ms_connect_arg_for_array(t_cmd *cmd)
{
	int y_arr;
	int x;
	int y;
	int start;
	int len;

	y_arr = 0;
	x = 0;
	y = 0;
	len = 0;
	start = 0;
	ms_malloc_array(&cmd->array_arg, cmd->num_array_arg);
	while (y < cmd->num_arg)
	{
		while (cmd->arg[y].str[x] != '\0')
			x++;
		len += x;
		x = 0;
		if ((cmd->arg[y].space == YES && cmd->arg[y].empty_key == NO) || (y + 1) == cmd->num_arg)
		{
			len = ms_record_arg(cmd, &cmd->array_arg[y_arr], &start, len);
			y_arr++;
		}
		y++;
	}
	cmd->array_arg[y_arr] = NULL;
}

int	ms_record_arg(t_cmd *cmd, char **str, int *i, int size_str)
{
	int x;
	int size_copy;

	x = 0;
	size_copy = 0;
	ms_malloc_str(str, size_str);
	while (size_copy < size_str)
	{
		while (cmd->arg[(*i)].str[x] != '\0')
		{
			(*str)[size_copy + x] = cmd->arg[(*i)].str[x];
			x++;
		}
		size_copy += x;
		x = 0;
		(*i)++;
	}
	(*str)[size_copy] = '\0';
	return (0);
}
