/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_and_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:41:25 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/13 13:23:01 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_redirect(t_cmd *cmd)
{
	if (cmd->fd[1] != 0)
	{
		dup2 (cmd->fd[1], 1);
		close (cmd->fd[1]);
	}
	if (cmd->fd[0] != 0)
	{
		dup2 (cmd->fd[0], 0);
		close (cmd->fd[0]);
	}
	return (0);
}

static void	ms_pipe_2(t_data *data, int last, int i)
{
	if (last != -1 && (data->cmd[i].redir[last] == 3
			|| data->cmd[i].redir[last] == 4))
		return ;
	if (pipe(data->fd_pipe) == -1)
		perror("fd[1]");
	dup2(data->fd_pipe[1], 1);
	close(data->fd_pipe[1]);
	//close(data->fd_pipe[0]);
}

void	ms_pipe(t_data *data, int i, int last)
{
	if (i > 0 && !data->cmd[i].redir_born[0])
	{
		if (last != -1 && (data->cmd[i - 1].redir[last] == 3
				|| data->cmd[i - 1].redir[last] == 4))
		{
			data->cmd[i].fd[0] = open("tmp", O_CREAT | O_RDONLY
					| O_TRUNC, 0644);
			if (dup2(data->cmd[i].fd[0], 0) == -1)
				perror("fd[0]");
			if (close(data->cmd[i].fd[0]) == -1)
				perror("fd[0]");
			return ;
		}
		if (dup2(data->fd_pipe[0], 0) == -1)
			perror("fd[0]");
		if (close(data->fd_pipe[0]) == -1)
			perror("fd[0]");
	}
	if (i < data->num_cmd - 1 && !data->cmd[i].redir_born[1])
		ms_pipe_2(data, last, i);
}
