/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:01:07 by obeedril          #+#    #+#             */
/*   Updated: 2022/02/18 19:47:06 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void ms_signal_ctrl_d(char *line)
{
	if (line == NULL)
	{
		printf("\033[1;36m\bMiMiShell >\033[0A"); 
		printf("\033[1;0m exit\n\033[0m");
		exit(EXIT_SUCCESS);
	}
}