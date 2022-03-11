/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:39:51 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/11 20:20:23 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_execve(t_cmd *cmd, t_data *data, int i)
{
	pid_t	pid;

	ms_check_first_arg(data, i);
	if (data->num_error != 0)
	{
		if (data->num_cmd > 1 && i < data->num_cmd - 1)
			data->num_error = 0;
		return ;
	}
	data->build_in = NO;
	pid = fork();
	if (pid == -1)
		perror("fork error");
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		// if (execve(cmd[i].array_arg[0], cmd[i].array_arg, data->our_env) == -1)
		// 	perror("execve ");
		if (execve(cmd[i].way_cmd, cmd[i].array_arg, data->our_env) == -1)
			perror("execve ");
		exit (0);
	}
}
