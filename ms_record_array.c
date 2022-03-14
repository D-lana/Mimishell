/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_record_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:43:48 by dlana             #+#    #+#             */
/*   Updated: 2022/03/13 15:19:43 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_count_arg_for_array(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->num_array_arg = 1;
	while (i < cmd->num_arg)
	{
		if (cmd->arg[i].space == YES)
			cmd->num_array_arg++;
		i++;
	}
}

int	ms_record_arg(t_cmd *cmd, char **str, int *i, int size_str)
{
	int	x;
	int	size_copy;

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

int	ms_len_arg_in_array(t_cmd *cmd, int y, int len)
{
	int	x;

	x = 0;
	while (cmd->arg[y].str[x] != '\0')
			x++;
	len += x;
	return (len);
}

void	ms_connect_arg_for_array(t_cmd *cmd)
{
	int	y_arr;
	int	y;
	int	start;
	int	len;

	y_arr = 0;
	y = 0;
	len = 0;
	start = 0;
	ms_malloc_array(&cmd->array_arg, cmd->num_array_arg);
	cmd->array_empty = NO;
	while (y < cmd->num_arg)
	{
		len = ms_len_arg_in_array(cmd, y, len);
		if ((cmd->arg[y].space == YES) || (y + 1) == cmd->num_arg)
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
	{
		while (i < data->num_cmd)
		{
			data->cmd[i].array_empty = YES;
			i++;
		}
		return ;
	}
	while (i < data->num_cmd)
	{
		data->cmd[i].array_empty = YES;
		if (data->cmd[i].str != NULL)
		{
			ms_count_arg_for_array(&data->cmd[i]);
			ms_connect_arg_for_array(&data->cmd[i]);
		}
		i++;
	}
	if (data->num_error == 0 && data->cmd[0].str != NULL)
		ms_found_variable(data);
}
