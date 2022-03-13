/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:10:20 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/13 13:23:22 by obeedril         ###   ########.fr       */
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
		if (i == 0)
		{
			if (close(data->fd_pipe[0]) == -1)
				perror("fd_pipe[0]ch");
			//close(1);
			// if (close(data->fd_pipe[1]) == -1)
			// 	perror("fd_pipe[1]ch");
		}
		// if (close(stdio[1]) == -1)
		// 	perror("stdio[1]c");
		//close(5);
		//close(6);
		if (execve(cmd[i].way_cmd, cmd[i].array_arg, data->our_env) == -1)
			perror("execve ");
		exit (0);
	}
}
