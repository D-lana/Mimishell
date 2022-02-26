/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 13:00:12 by obeedril          #+#    #+#             */
/*   Updated: 2022/02/26 13:31:11 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// << txt
// signal

static void ms_write_in_heredoc(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
	free(str);
}

int ms_heredoc(t_cmd *cmd, t_data *data)
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
				//get_next_line(&str);
				
				if (!str)
				{
					rl_on_new_line();
					rl_replace_line("\b", 0);
					//rl_on_new_line();
					rl_redisplay();
					
					break ;
				}
				//	break ;
				if (ft_strncmp(*cmd->file, str, ft_strlen(*cmd->file)) == 0)
				{
					write (1, "A\n", 2);
					printf("%s\n", *cmd->file);
					free (str);
					write (1, "B\n", 2);
					break ;
				}
				//else
					ms_write_in_heredoc(cmd->fd[1], str);
			}
			exit (0);
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(0, &status, 0);
		if (WIFSIGNALED(status) > 0)
		{
			termsig = WTERMSIG(status);
			if (termsig == 2)
				write(1, ">   \b\b\b\n", 8);
		}
	//	ms_get_signal();
		cmd->fd[0] = open(*cmd->file, O_RDONLY, 0644);
		close(cmd->fd[1]);
		// close(cmd->fd[0]);
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
			ms_heredoc(cmd, data);
			unlink(cmd->file[i]);
		}
		i++;
	}
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

// void ms_pipe(t_data *data, t_cmd **cmd, int i)
// {
// 	//printf("cmd[i] = %s\n", cmd[i]->array_arg[0]);
// 	//if (i > 0 && !(cmd[i]->fd[0]))
// 	printf("cmd->fd[0] = %d\n", cmd[i]->fd[0]);
// 	if ((!cmd[i]->fd[0]) && i > 0)
// 	{
// 		write (1, "A\n", 2);
// 		dup2(cmd[i]->fd[0], 0);
// 		close (cmd[i]->fd[0]);
// 	}
// 	if ((!cmd[i]->fd[1]) && i < data->num_cmd) //&& i > 0))
// 	{
// 		write (1, "B\n", 2);
// 		if (pipe(cmd[i]->fd) != 0)
// 			perror("pipe ");
// 		write (1, "D\n", 2);
// 		dup2(cmd[i]->fd[1], 1);
// 		write (1, "E\n", 2);
// 		close (cmd[i]->fd[1]);
// 		write (1, "F\n", 2);
// 	}
// }

void ms_execution(t_data *data, t_cmd **cmd, char **env)
{
	int i;
	int		stdio[2];
	(void) env;
	
	i = 0;
	stdio[0] = dup(0);
	stdio[1] = dup(1);
	while (i < data->num_cmd)
	{
		if (data->count_redir != 0)
		{
			ms_open_file(cmd[i], data);
			ms_redirect(cmd[i]);
		}
		// else
		// {
		// // write (1, "D\n", 2);
		// 	if (data->num_cmd > 1)
		// 		ms_pipe(data, &cmd[i], i);
		// }
		// write (1, "E\n", 2);
		//printf("cmd[i] = %s\n", cmd[i]->array_arg[0]);
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
