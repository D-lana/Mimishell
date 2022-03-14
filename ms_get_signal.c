/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:01:52 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/13 20:20:21 by dlana            ###   ########.fr       */
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
	exit_st = WEXITSTATUS(status);
	if (exit_st > 0)
	{
		data->num_error = exit_st;
		if (exit_st != 1 && exit_st != 2 && exit_st != 126
			&& exit_st != 128 && exit_st != 130 && exit_st != 258)
			data->num_error = 127;
	}
	if (WIFSIGNALED(status) > 0)
		ms_exe_signal_2(status);
}
