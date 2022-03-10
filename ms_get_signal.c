#include "minishell.h"

static void	sighandler(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b\n", 5);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

int	ms_get_signal(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

void	ms_signal_ctrl_d(t_data *data, char **line)
{
	(void)data;
	if (*line == NULL)
	{
		printf("\033[1;35m\bMiMiShell >\033[0A"); 
		printf("\033[1;0m exit\n\033[0m");
		//ms_free_all(data, line);
		exit(EXIT_SUCCESS);
	}
}

void	ms_exe_signal(t_data *data)
{
	int	status;
	int	termsig;
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

void	ms_heredoc_signal(pid_t pid)
{
	int status;
	int termsig;

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