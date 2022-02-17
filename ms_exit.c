/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:15:18 by obeedril          #+#    #+#             */
/*   Updated: 2022/02/17 16:32:41 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit(t_data *data, char *exit_arg, int i)
{
	(void)data;
	(void)i;
	(void)exit_arg;
	if (!exit_arg)
		exit (EXIT_SUCCESS);
	// else
	// {
	// 	printf("exit_arg = %s\n", exit_arg);
	// 	//printf("num_args = %d\n", data->cmd->num_array_arg);
	// 	// if (data->cmd->num_array_arg > 1)
	// 	// {
	// 	// 	data->num_error = 1;
	// 	// 	printf("exit\n");
	// 	// 	printf("Mimishell: exit: too many arguments");
	// 	// }	
	// }
}