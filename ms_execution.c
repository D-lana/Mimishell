
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 13:00:12 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/03 18:25:41 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ms_write_in_heredoc(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
	free(str);
}

int ms_heredoc(t_cmd *cmd, t_data *data, int i)
{
	char *str;
	pid_t pid;

	if(data->num_error == 0)
	{
		if ((pid = fork()) == -1)
			perror("fork error");
		if (pid == 0)
		{
			while (1)
			{
				signal(SIGINT, SIG_DFL);

				str = readline("> ");
				if (!str)
				{
					rl_redisplay();
					rl_on_new_line();
					break ;
				}
					if (ft_strncmp(cmd->file[i], str, ft_strlen(cmd->file[i])) == 0)
					{
						free (str);
							break ;
					}
					else
						ms_write_in_heredoc(cmd->fd[1], str);
			}
			exit (0);
		}
		ms_heredoc_signal(pid);
		cmd->fd[0] = open(cmd->file[i], O_RDONLY, 0644);
		 close(cmd->fd[1]);
	}
	return (0);
}

int ms_check_file(t_cmd *cmd, int i)
{
	int		j;
	char	*str;
	char	*str_slesh;
	char	*str_way;
	int		mistake;

	j = 0;
	mistake = 0;
	str = NULL;
	str_way = NULL;
	str_slesh = NULL;
	str = getcwd(NULL, 0);
	str_slesh = ft_strjoin(str, "/");
	str_way = ft_strjoin(str_slesh, cmd->file[i]);
	ms_free_str(&str_slesh);
	if (!access (str_way, 0))
		mistake = 1;
	ms_free_str(&str_way);
	return (mistake);
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
			cmd->fd[1] = open(cmd->file[i], O_CREAT | O_WRONLY  | O_APPEND, 0644);
		if (cmd->redir[i] == 2)
		{
			if (ms_check_file(cmd, i) == 1)
				cmd->fd[0] = open(cmd->file[i], O_RDONLY, 0644);
			else
			{
				ms_print_errors_chfa(cmd->file[i], 4);
				cmd->bad_file = YES;
			}
		}
		if (cmd->redir[i] == 5)
		{
			cmd->fd[1] = open(cmd->file[i], O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
			if (cmd->fd[0] > 0)
				close(cmd->fd[0]);
			ms_heredoc(cmd, data, i);

		}
		if (cmd->redir[i] == 6)
		{
			cmd->fd[0] = open(cmd->file[i], O_CREAT |O_RDONLY | O_TRUNC, 0644);
			cmd->fd[1] = open(cmd->file[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		i++;
	}
	cmd->redir_born[0] = cmd->fd[0];
	cmd->redir_born[1] = cmd->fd[1];
}

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

void ms_pipe(t_data *data, int i, int last)
{
	if (i > 0 && !data->cmd[i].redir_born[0])
	{
		if (last != -1 && (data->cmd[i - 1].redir[last] == 3 
			|| data->cmd[i - 1].redir[last] == 4))
		{
			data->cmd[i].fd[0] = open("tmp", O_CREAT | O_RDONLY | O_TRUNC, 0644);
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
	{
		if (last != -1 && (data->cmd[i].redir[last] == 3
			|| data->cmd[i].redir[last] == 4))
			return ;
		if (pipe(data->fd_pipe) == -1)
			perror("fd[1]");
		dup2(data->fd_pipe[1], 1);
		close(data->fd_pipe[1]);
	}
}

int find_last_redir(int last, t_data *data)
{
	int i;

	i = 0;
	while (data->cmd->redir[i])
	{
		if (data->cmd->redir[i] == 3 || data->cmd->redir[i] == 4)
			last = i;
		i++;
	}
	return (last);
}

void ms_execution(t_data *data)
{
	int		i;
	int		stdio[2];
	int j;
	int last;
	
	i = 0;
	j = 0;
	last = -1;
	if (data->num_error != 0)
		return ;
	stdio[0] = dup(0);
	stdio[1] = dup(1);
	while (i < data->num_cmd)
	{
		data->cmd[i].bad_file = NO;
		if (data->cmd[i].count_redir != 0)
		{
			ms_open_file(&data->cmd[i], data);
			ms_redirect(&data->cmd[i]);
			last = find_last_redir(last, data);
		}
		if (data->num_cmd > 1)
			ms_pipe(data, i, last);
		if (data->cmd[i].bad_file == NO)
			ms_our_cmd(data, i);
		if (data->cmd[i].count_redir != 0)
		{
			while (data->cmd[i].file[j])
			{
				if (data->cmd[i].redir[j] == 5)
					unlink(data->cmd[i].file[j]);
				j++;
			}
		}
		if (data->num_cmd > 1)
			dup2(stdio[1], STDOUT_FILENO);
		i++;
	}
	if (data->num_cmd > 1 || (data->build_in == NO && data->num_cmd == 1))
		ms_exe_signal(data);
	if (dup2(stdio[1], 1) == -1)
		perror("dup2 ");
	if (dup2(stdio[0], 0) == -1)
		perror("dup2 ");
	close(stdio[0]);
	close(stdio[1]);
}
