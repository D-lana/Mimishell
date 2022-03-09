/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:15:18 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/09 19:46:36 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
		{
			if (str[0] == 45)
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	exit_with_args(t_data *data, int num_array_arg, char *exit_arg)
{
	int	error_code;

	error_code = 0;
	if (ft_isnum(exit_arg) == 1)
	{
		ms_print_error_builtin(exit_arg, 4);
		exit (255);
	}
	else
	{
		if (num_array_arg > 2)
		{
			data->num_error = 1;
			ms_print_error_builtin(NULL, 5);
		}
		else
		{
			error_code = ft_atoi(exit_arg);
			printf("\bexit\n");
			exit (error_code);
		}
	}
}

void	ms_exit(t_data *data, int num_array_arg, char *exit_arg)
{
	if (!exit_arg)
	{
		printf("exit\n");
		exit (0);
	}
	else
		exit_with_args(data, num_array_arg, exit_arg);
}
