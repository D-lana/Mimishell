#include "minishell.h"

// void ms_printf_array(t_data *data)
// {
// 	int	i;
// 	int y;

// 	i = 0;
// 	y = 0;
// 	printf("data->num_cmd = %d\n", data->num_cmd);
// 	printf("data->cmd[y].num_array_arg = %d\n", data->cmd[y].num_array_arg);
// 	while (y < data->num_cmd)
// 	{
// 		while (i < data->cmd[y].num_array_arg)
// 		{
// 			printf("in arr |%s| \n", data->cmd[y].array_arg[i]);
// 			i++;
// 		}	
// 		y++;
// 		i = 0;
// 	}
// 	//printf("\n");
// }

void	ms_count_arg_for_array(t_cmd *cmd)
{
	int i;

	i = 0;
	cmd->num_array_arg = 1;
	while (i < cmd->num_arg)
	{
		if (cmd->arg[i].space == YES) // && cmd->arg[i].empty_key == NO)
			cmd->num_array_arg++;
		i++;
	}
}

int	ms_record_arg(t_cmd *cmd, char **str, int *i, int size_str)
{
	int x;
	int size_copy;

	x = 0;
	size_copy = 0;
	ms_malloc_str(str, size_str);
	//printf("alloc str cmd->array_arg[y]\n");
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
	//printf("alloc cmd->array_arg\n");
	cmd->array_empty = NO;
	while (y < cmd->num_arg)
	{
		while (cmd->arg[y].str[x] != '\0')
			x++;
		len += x;
		x = 0;

		if ((cmd->arg[y].space == YES) || (y + 1) == cmd->num_arg) // && cmd->arg[y].empty_key == NO)
		{
			len = ms_record_arg(cmd, &cmd->array_arg[y_arr], &start, len);
			y_arr++;
		}
		y++;
	}
	cmd->array_arg[y_arr] = NULL;
}

void	ms_record_array(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_error != 0)
		return ;
	while (i < data->num_cmd)
	{
		data->cmd[i].array_empty = YES;
		// if (data->cmd[i].str == NULL)
		// {
		// 	//write(2, "empty.str\n", 11);
		// }
		if (data->cmd[i].str != NULL)
		{
			ms_count_arg_for_array(&data->cmd[i]);
			ms_connect_arg_for_array(&data->cmd[i]);
		}
		i++;
	}
	//ms_printf_array(data); ///// распечатка убрать
	if(data->num_error == 0 && data->cmd[0].str != NULL)
		ms_found_variable(data);
}
