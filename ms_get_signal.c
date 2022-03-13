/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:01:52 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/13 15:59:18 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

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
	if (*line == NULL)
	{
		printf("\033[1;35m\bMiMiShell >\033[0A");
		printf("\033[1;0m exit\n\033[0m");
		ms_free_all(data, line);
		exit(EXIT_SUCCESS);
	}
}

static void	ms_exe_signal_2(int status)
{
	int	termsig;

	termsig = 0;
	termsig = WTERMSIG(status);
	if (termsig == 2)
		write(1, "\n", 2);
	if (termsig == 3)
		printf("Quit: %d\n", status);	
}

// static void ms_yes(t_data *data, int *status)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->num_cmd)
// 	{
// 		if (ft_strncmp(data->cmd[i].array_arg[0], "yes\0", 4) == 0)
// 		{
// 			return ;
// 		}
// 		i++;
// 	}
// 	waitpid(-1, status, 0);
// }

void	ms_child_sig_3(int sig)
{
	(void) sig;
	exit(4);
}

void ms_exe_signal(t_data *data, int *stdio)
{
	int status;
	int termsig;
	int	exit_st;
	int	i;
	(void)stdio;

	i = 0;
	termsig = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close(0);
	while (data->num_cmd > i)
	{
		// if (i == 0)
		// {
		// 	if (close(stdio[0]) == -1)
		// 		perror("stdio_par");
		// }
		waitpid(-1, &status, 0);
		i++;
	}
	//ms_yes(data, &status);
	exit_st = WEXITSTATUS(status);
	if (exit_st > 0)
    {
        data->num_error = exit_st;
        if(exit_st != 1 && exit_st != 2 && exit_st != 126
            && exit_st != 128 && exit_st != 130 && exit_st != 258)
            data->num_error = 127;
    }
	if (WIFSIGNALED(status) > 0)
		ms_exe_signal_2(status);
}
