/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 13:00:12 by obeedril          #+#    #+#             */
/*   Updated: 2022/02/23 17:45:41 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_open_file(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->file[i])
	{
		// if (cmd->redir[i] == 2)
		// 	cmd->fd[1] = open(cmd->file[i], O_RDONLY, 0644);
		if (cmd->redir[i] == 3)
			cmd->fd[1] = open(cmd->file[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			//printf("cmd->fd[1] start = %d\n", cmd->fd[1]);
		// if (cmd->redir[i] == 4)
		// 	cmd->fd[1] = open(cmd->file[i], O_CREAT | O_WRONLY  | O_APPEND, 0644);
		// if (cmd->redir[i] == 5)
		// 	cmd->fd[1] = open(cmd->file[i], O_RDONLY, 0644);

		i++;
	}
	return (0);
}

int	ms_redirect(t_cmd *cmd)
{
	if (cmd->fd[1] != 0)
	{
		dup2 (cmd->fd[1], 1);  // ?????????
		close (cmd->fd[1]);
	}
	return (0);
}

void ms_execution(t_data *data, t_cmd **cmd, char **env)
//void ms_execution(t_data *data, t_cmd **cmd)
{
	int i;
	int		stdio[2];
	(void) env;
	
	i = 0;
	stdio[0] = dup(0);
	stdio[1] = dup(1);
	while (i < data->num_cmd)
	{
		ms_open_file(cmd[i]);
		ms_redirect(cmd[i]);
		//ms_pipe();
		if (!cmd[i]->fd[0] && i < 0)
		{
			dup2(cmd[i]->fd[0], 0);
			close (cmd[i]->fd[0]);
		}
		if (!cmd[i]->fd[1] && i < data->num_cmd)
		{
			pipe(cmd[i]->fd);
			dup2(cmd[i]->fd[1], 1);
			close (cmd[i]->fd[1]);
		}
		ms_our_cmd(data, i);
		i++;
	}
	if (dup2(stdio[1], 1) == -1) // return 1;
		perror("dup2 ");
	if (dup2(stdio[0], 0) == -1) // return 0;
		perror("dup2 ");
	close(stdio[0]);
	close(stdio[1]);
}
