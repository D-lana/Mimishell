/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:39:51 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/07 16:28:57 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_execve(t_cmd *cmd, t_data *data, int i)
{
	pid_t pid;

	ms_check_first_arg(data);
	if (data->num_error != 0 || data->empty_str == YES)
		return ;
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
