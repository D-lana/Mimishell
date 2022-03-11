/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:06:50 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/11 19:28:32 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_heredoc_signal(pid_t pid)
{
	int	status;
	int	termsig;

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
}

static void	ms_write_in_heredoc(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
	free(str);
}

static int	ms_heredoc_2(t_cmd *cmd, int i)
{
	char	*str;

	str = NULL;
	signal(SIGINT, SIG_DFL);
	str = readline("> ");
	if (!str)
	{
		rl_redisplay();
		rl_on_new_line();
		return (-1);
	}
	if (ft_strncmp(cmd->file[i], str, ft_strlen(cmd->file[i])) == 0)
	{
		free (str);
		return (-1);
	}
	else
		ms_write_in_heredoc(cmd->fd[1], str);
	return (0);
}

int	ms_heredoc(t_cmd *cmd, t_data *data, int i)
{
	pid_t	pid;

	if (data->num_error == 0)
	{
		pid = fork();
		if (pid == -1)
			perror("fork error");
		if (pid == 0)
		{
			while (1)
			{
				printf("cmd->file = %s\n", cmd->file[i]);
				if (ms_heredoc_2(cmd, i) == -1)
					break ;
			}
			exit (0);
		}
		ms_heredoc_signal(pid);
		cmd->fd[0] = open(cmd->file[i], O_RDONLY, 0644);
		close(cmd->fd[1]);
	}
	return (0);
}
