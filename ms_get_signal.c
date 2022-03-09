/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:13:10 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/09 18:14:16 by obeedril         ###   ########.fr       */
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
