#include "minishell.h"
 
static void exe_signal(t_data *data)
{
	int status;
	int termsig;
	int	exit_st;

	termsig = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(0, &status, 0);
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

void	ms_execve(t_cmd *cmd, t_data *data, int i)
{
	pid_t pid;

	ms_check_first_arg(data);
	if (data->num_error != 0 || data->empty_str == YES)
		return ;
	if ((pid = fork()) == -1)
		perror("fork error");
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (cmd[i].array_arg[0][0] == '.' && cmd[i].array_arg[0][1] == '/')
		{
			if (execve(cmd[i].cur_way_cmd, cmd[i].array_arg, data->our_env) == -1)
				perror("execve ");
		}
		else
		{
			if (execve(cmd[i].way_cmd, cmd[i].array_arg, data->our_env) == -1)
				perror("execve ");
		}
		exit (0);
	}
	exe_signal(data);
}