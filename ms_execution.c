
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

// bash-3.2$ < txt1
//bash: txt1: No such file or directory

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
	int status;
	int termsig;

	if(data->num_error == 0 && data->empty_str == NO)
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
		if (pid != 0)
			signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(0, &status, 0);
		if (WIFSIGNALED(status) > 0)
		{
			termsig = WTERMSIG(status);
			if (termsig == 2)
				write(1, ">   \b\b\b\n", 8);
		}
		cmd->fd[0] = open(cmd->file[i], O_RDONLY, 0644);
		 close(cmd->fd[1]);
	}
	return (0);
}

void	ms_open_file(t_cmd *cmd, t_data *data)
{
	int i;

	i = 0;
	while (cmd->file[i])
	{
		if (cmd->redir[i] == 3)
			cmd->fd[1] = open(cmd->file[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (cmd->redir[i] == 4)
			cmd->fd[1] = open(cmd->file[i], O_CREAT | O_WRONLY  | O_APPEND, 0644);
		if (cmd->redir[i] == 2)
			cmd->fd[0] = open(cmd->file[i], O_RDONLY, 0644);
		if (cmd->redir[i] == 5)
		{
			cmd->fd[1] = open(cmd->file[i], O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
			if (cmd->fd[0] > 0)
				close(cmd->fd[0]);
			ms_heredoc(cmd, data, i);

		}
		i++;
	}
	cmd->redir_born[0] = cmd->fd[0];
	cmd->redir_born[1] = cmd->fd[1];
	//printf("redir_born[0] = %d\n", cmd->redir_born[0]);
	//printf("redir_born[1] = %d\n", cmd->redir_born[1]);
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

void ms_pipe(t_data *data, int i)
{
	if (i > 0 && !data->cmd[i].redir_born[0])
	{
		if (dup2(data->fd_pipe[0], 0) == -1)
			perror("fd[0]");
		if (close(data->fd_pipe[0]) == -1)
			perror("fd[0]");
	}
	if (i < data->num_cmd - 1 && !data->cmd[i].redir_born[1])
	{
		if (pipe(data->fd_pipe) == -1)
			perror("fd[1]");
		dup2(data->fd_pipe[1], 1);
		close(data->fd_pipe[1]);
	}
}

static void exe_signal(t_data *data)
{
	int status;
	int termsig;
	int	exit_st;
	int	i;

	i = 0;
	termsig = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (data->num_cmd > i)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	waitpid(-1, &status, 0);
	exit_st = WEXITSTATUS(status);
	if (exit_st > 0)
		data->num_error = exit_st;
	if (WIFSIGNALED(status) > 0)
	{
		termsig = WTERMSIG(status);
		if (termsig == 2)
			write(1, "\n", 1);
		if (termsig == 3)
			printf("Quit: %d\n", status);
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
	stdio[0] = dup(0);
	stdio[1] = dup(1);
	while (i < data->num_cmd)
	{
		if (data->cmd[i].count_redir != 0)
		{
			ms_open_file(&data->cmd[i], data);
			ms_redirect(&data->cmd[i]);
			last = find_last_redir(last, data);
		}
		if (data->num_cmd > 1)
				ms_pipe(data, i);
		ms_our_cmd(data, i);
		if (data->cmd[i].count_redir) // i == 0  data->num_cmd > 1
		{
			if (data->cmd[i].redir[last] == 3 || data->cmd[i].redir[last] == 4)
				break ;
		}
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
		exe_signal(data);
	if (dup2(stdio[1], 1) == -1) // return 1;
		perror("dup2 ");
	if (dup2(stdio[0], 0) == -1) // return 0;
		perror("dup2 ");
	close(stdio[0]);
	close(stdio[1]);
}
