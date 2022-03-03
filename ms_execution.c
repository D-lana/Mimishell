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

void ms_pipe(t_data *data, int i)
{
	if (i > 0)
	{
		if (dup2(data->fd_pipe[0], 0) == -1)
			perror("fd[0]");
		if (close(data->fd_pipe[0]) == -1)
			perror("fd[0]");
	}
	if (i < data->num_cmd - 1)
	{
		if (pipe(data->fd_pipe) == -1)
			perror("fd[1]");
		dup2(data->fd_pipe[1], 1);
		close(data->fd_pipe[1]);
	}
}

void ms_execution(t_data *data)
{
	int		i;
	int		stdio[2];
	
	i = 0;
	stdio[0] = dup(0);
	stdio[1] = dup(1);
	while (i < data->num_cmd)
	{
		if (data->cmd[i].count_redir != 0)
		{
			ms_open_file(&data->cmd[i], data);
			ms_redirect(&data->cmd[i]);
		}
		if (data->num_cmd > 1)
			ms_pipe(data, i);
		ms_our_cmd(data, i);
		if (data->num_cmd > 1)
			dup2(stdio[1], STDOUT_FILENO);
		i++;
	}
	//write (2, "Escape while\n", 14);
	if (dup2(stdio[1], 1) == -1) // return 1;
		perror("dup2 ");
	if (dup2(stdio[0], 0) == -1) // return 0;
		perror("dup2 ");
	close(stdio[0]);
	close(stdio[1]);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

// void	ft_child(t_data *data, int i)
// {
// 	if (i < data->num_cmd - 1)
// 	{
// 		write (2, "i < data->num_cmd\n", 19);
// 		dup2(data->fd_pipe[1], STDOUT_FILENO);
// 		close(data->fd_pipe[1]);
// 		//close(data->fd_pipe[0]);
// 	}
// 	write (2, "Child 1\n", 9);
// 	ms_our_cmd(data, i);
// 	exit (EXIT_FAILURE);
// }

// void ms_execution(t_data *data, t_cmd *cmd, char **env)
// {
// 	int i;
// 	int		stdio[2];
// 	(void) env;
// 	(void) cmd;
// 	int status;
// 	pid_t	child;
	
// 	i = 0;
// 	stdio[0] = dup(0);
// 	stdio[1] = dup(1);
// 	while (i < data->num_cmd)
// 	{
// 		if (data->count_redir != 0)
// 		{
// 			ms_open_file(&cmd[i], data);
// 			ms_redirect(&cmd[i]);
// 			ms_our_cmd(data, i);
// 		}
// 		if (data->num_cmd > 1)
// 		{
// 			write (1, "Before\n", 8);
// 			if (i < data->num_cmd - 1)
// 			{
// 				if (pipe(data->fd_pipe) < 0) // error
// 					exit(write (2, "Error: Pipe\n", 13));
// 			}
// 			//close(data->fd_pipe[1]);
// 			child = fork();
// 			if (child < 0) // error
// 				exit(2);
// 			if (child == 0)
// 				ft_child(data, i);
// 			//write (2, "Child 2", 8);
// 			//close(data->fd_pipe[1]);
// 			dup2(data->fd_pipe[0], STDIN_FILENO);
// 			close(data->fd_pipe[0]);
// 			close(data->fd_pipe[1]);
// 			waitpid(0, &status, 0);
// 			write (2, "After\n", 7);
// 		}
// 		else
// 			ms_our_cmd(data, i);
// 		i++;
// 	}
// 	write (2, "Escape while\n", 14);
// 	if (dup2(stdio[1], 1) == -1) // return 1;
// 		perror("dup2 ");
// 	if (dup2(stdio[0], 0) == -1) // return 0;
// 		perror("dup2 ");
// 	close(stdio[0]);
// 	close(stdio[1]);
// }


