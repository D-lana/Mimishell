/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:42:28 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/14 16:11:37 by dlana            ###   ########.fr       */
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

static int	ms_check_directory(t_data *data, t_cmd *cmd, int i)
{
	if (opendir(cmd->file[i]) != NULL)
	{
		data->num_error = ERR_NUM_ONE;
		ms_print_errors_chfa(cmd->file[i], 2);
		return (-1);
	}
	return (0);
}

void	ms_open_file(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	if (ms_check_directory(data, cmd, i) == -1)
		return ;
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
