/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:39:51 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/08 12:41:28 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_execve(t_cmd *cmd, t_data *data, int i)
{
	pid_t pid;

	// if (data->num_error != 0 || data->empty_str == YES)
	// 	return ;
	ms_check_first_arg(data, i);
	if (data->num_error != 0)
	{
		if (data->num_cmd > 1 && i < data->num_cmd - 1)
			data->num_error = 0;
		return ;
	}
	data->build_in = NO;
	if ((pid = fork()) == -1)
		perror("fork error");
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (execve(cmd[i].way_cmd, cmd[i].array_arg, data->our_env) == -1)
			perror("execve ");
		exit (0);
	}
}
