#include "minishell.h"

static void	ft_child(t_data *data, int *fd, int i)
{
	if (i < 2)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	if (i == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		char *cmd[] = {"pwd", NULL};
		if (execve("/bin/pwd", cmd, data->our_env) == -1)
			write (2, "Error: Command not found: ", 27);
		exit(0);
	}
	else if (i == 1)
	{
		signal(SIGQUIT, SIG_DFL);
		char *cmd[] = {"grep", "dlana", NULL};
		if (execve("/usr/bin/grep", cmd, data->our_env) == -1)
			write (2, "Error: Command not found: ", 27);
		exit(0);
	}
	else if (i == 2)
	{
		signal(SIGQUIT, SIG_DFL);
		char *cmd[] = {"wc", "-l", NULL};
		if (execve("/usr/bin/wc", cmd, data->our_env) == -1)
			write (2, "Error: Command not found: ", 27);
		exit(0);
	}
	exit (EXIT_FAILURE);
}

void	ms_exe(t_data *data)
{
	int	fd[2];
	int	child;
	int i;
	int status;
	int termsig;
	int	exit_st;
	
	termsig = 0;
	
	i = 0;
	while (i < 3)
	{
		if (i < 3 - 1)
		{
			if (pipe(fd) < 0) // error
				exit(write (2, "Error: Pipe\n", 13));
		}
		child = fork();
		if (child < 0) // error
			exit(2);
		if (child == 0)
			ft_child(data, fd, i);
		//write (2, "Child 2", 8);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		i++;
		waitpid(0, &status, 0);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	exit_st = WEXITSTATUS(status);
	if (exit_st > 0)
		data->num_error = exit_st;
	if (WIFSIGNALED(status) > 0)
	{	
		termsig = WTERMSIG(status);
		if (termsig == 2)
			write(1, "\n", 1);
		if (termsig == 3)
		{
			printf("Quit: %d\n", status);
		}
	}
	// i = 0;
	write (2, "Escape pipe\n", 13);
	// while (i < data->num_cmd)
	// {
	// 	wait(NULL);
	// 	i++;
	// }
	write (2, "Escape pipe\n", 13);
	//wait(NULL);
	//wait(NULL);
	//wait(NULL);
	// waitpid(child_2, NULL, 0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	// int num_cmd = 3;
// 	// while (num_cmd > 0)
// 	// {
// 		ft_pipex(env);
// 	// 	num_cmd--;
// 	// }
// 	exit(EXIT_SUCCESS);
// }
