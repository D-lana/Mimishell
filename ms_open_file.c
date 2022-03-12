/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:42:28 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/11 21:28:02 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_open_redir_2(t_cmd *cmd, int i)
{
	if (ms_check_file(cmd, i) == 1)
		cmd->fd[0] = open(cmd->file[i], O_RDONLY, 0644);
	else
	{
		ms_print_errors_chfa(cmd->file[i], 4);
		cmd->bad_file = YES;
	}
}

static void	ms_open_redir_5(t_cmd *cmd, t_data *data, int i)
{
	cmd->fd[1] = open(cmd->file[i], O_WRONLY | O_CREAT
			| O_TRUNC | O_APPEND, 0644);
	if (cmd->fd[0] > 0)
		close(cmd->fd[0]);
	ms_heredoc(cmd, data, i);
}

void	ms_open_file(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd->file[i])
	{
		if (cmd->redir[i] == 3)
			cmd->fd[1] = open(cmd->file[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (cmd->redir[i] == 4)
			cmd->fd[1] = open(cmd->file[i], O_CREAT
					| O_WRONLY | O_APPEND, 0644);
		if (cmd->redir[i] == 2)
			ms_open_redir_2(cmd, i);
		if (cmd->redir[i] == 5)
			ms_open_redir_5(cmd, data, i);
		if (cmd->redir[i] == 6)
		{
			cmd->fd[0] = open(cmd->file[i], O_CREAT | O_RDONLY | O_TRUNC, 0644);
			cmd->fd[1] = open(cmd->file[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		i++;
	}
	cmd->redir_born[0] = cmd->fd[0];
	cmd->redir_born[1] = cmd->fd[1];
}
