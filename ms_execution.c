/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 13:00:12 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/13 20:24:01 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_last_redir(t_data *data, int i)
{
	int	j;

	j = 0;
	
	while (data->cmd[i].redir[j] != 0)
	{
		if (data->cmd[i].redir[j] == 3 || data->cmd[i].redir[j] == 4)
			data->cmd[i].last_redir = j;
		j++;
	}
	return (data->cmd[i].last_redir);
}

static void	ms_execution_2(t_data *data, int i, char **line)
{
	int	j;

	j = 0;
	data->cmd[i].last_redir = -1;
	data->cmd[i].bad_file = NO;
	if (data->cmd[i].count_redir != 0)
	{
		ms_open_file(&data->cmd[i], data);
		ms_redirect(&data->cmd[i]);
		find_last_redir(data, i);
	}
	if (data->num_cmd > 1)
		ms_pipe(data, i);
	if (data->cmd[i].bad_file == NO)
		ms_our_cmd(data, i, line);
	if (data->cmd[i].count_redir != 0)
	{
		while (j < data->cmd[i].count_redir)
		{
			
			if (data->cmd[i].redir[j] == 5)
				unlink(data->cmd[i].file[j]);
			j++;
		}
	}
}

void	ms_return_stdio(int *stdio)
{
	if (dup2(stdio[1], 1) == -1)
		perror("dup2 ");
	if (dup2(stdio[0], 0) == -1)
		perror("dup2 ");
	close(stdio[0]);
	close(stdio[1]);
}

void	ms_execution(t_data *data, char **line)
{
	int		i;
	int		stdio[2];

	i = 0;
	if (data->num_error != 0)
		return ;
	stdio[0] = dup(0);
	stdio[1] = dup(1);
	data->pid = 0;
	ms_malloc_arr_int(&data->pid, data->num_cmd);
	while (i < data->num_cmd)
	{
		if (ms_check_name(data, i) == -1)
			return ;
		ms_execution_2(data, i, line);
		if (data->num_cmd > 1)
			dup2(stdio[1], STDOUT_FILENO);
		i++;
	}
	data->pid[i] = 0;
	ms_return_stdio(stdio);
	if (data->num_cmd > 1 || (data->build_in == NO && data->num_cmd == 1
		&& !data->num_error))
		ms_exe_signal(data);
	ms_free_int_arr(&data->pid);
}
