/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:10:20 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/14 15:02:46 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_execve(t_cmd *cmd, t_data *data, int i)
{
	ms_check_first_arg(data, i);
	if (data->num_error != 0)
	{
		if (data->num_cmd > 1 && i < data->num_cmd - 1)
			data->num_error = 0;
		return ;
	}
	data->build_in = NO;
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		perror("fork error");
	else if (data->pid[i] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (i == 0 && data->fd_pipe[0])
		{
			if (close(data->fd_pipe[0]) == -1)
				perror("fd_pipe[0]ch");
		}
		if (execve(cmd[i].way_cmd, cmd[i].array_arg, data->our_env) == -1)
			perror("execve ");
		exit (0);
	}
}
