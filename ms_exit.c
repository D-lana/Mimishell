/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:15:18 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/11 22:31:28 by obeedril         ###   ########.fr       */
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

static void	exit_with_args_2(t_data *data, int num, char *exit_arg, char **line)
{
	long long int	exit_code;

	exit_code = 0;
	if (num > 2)
	{
		data->num_error = 1;
		ms_print_error_builtin(NULL, 5);
	}
	else
	{
		exit_code = ft_ll_atoi(exit_arg);
		if (exit_code == -1)
		{
			ms_print_error_builtin(exit_arg, 4);
			ms_free_all(data, line);
			exit (255);
		}
		else
		{
			printf("\bexit\n");
			ms_free_all(data, line);
			exit (exit_code);
		}
	}
}

static void	exit_with_args(t_data *data, int num, char *exit_arg, char **line)
{
	long long int	exit_code;

	exit_code = 0;
	if (ft_isnum(exit_arg) == 1)
	{
		ms_print_error_builtin(exit_arg, 4);
		ms_free_all(data, line);
		exit (255);
	}
	else
		exit_with_args_2(data, num, exit_arg, line);
}

void	ms_exit(t_data *data, int num, char *exit_arg, char **line)
{
	if (!exit_arg)
	{
		printf("exit\n");
		ms_free_all(data, line);
		exit (0);
	}
	else
		exit_with_args(data, num, exit_arg, line);
}
