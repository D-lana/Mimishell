/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_first_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:49:32 by obeedril          #+#    #+#             */
/*   Updated: 2022/02/19 12:21:02 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_slesh(char **arr_p, int i, int j)
{
	char	*str_slesh;

	ms_malloc_str(&str_slesh, ft_strlen(arr_p[i] + 1));
	while (arr_p[i][j] != '\0')
	{
		str_slesh[j] = arr_p[i][j];
		j++;
		if (arr_p[i][j] == '\0')
		{
			str_slesh[j] = '/';
			str_slesh[j + 1] = '\0';
		}
	}
	return (str_slesh);
}

static int	check_str(t_data *data, char **arr_p, int i, int n)
{
	int		find_cmd;
	char	*str_slesh;
	char	*str_way;

	find_cmd = 0;
	if (data->cmd[n].redir[0])
	{
		write (1, "Redirect!\n", 10);
		return (-1);
	}
	else
	{
		while (arr_p[i])
		{
			str_slesh = add_slesh(arr_p, i, 0);
			str_way = ft_strjoin(&str_slesh[0], data->cmd[n].array_arg[0]);
			if (!access (str_way, 1))
			{
				find_cmd = -1;
				// записать в структуру cmd путь, чтобы использовать в execve(адрес, массив, env)
				break ;
			}
			else
				find_cmd++;
			free(str_way);
			free(str_slesh);
			i++;
		}
		return (find_cmd);
	}
}

void	ms_check_first_arg(t_data *data)
{
	const char	*p;
	char		**arr_p;
	int			i;
	int			n;
	int			find_cmd;

	i = 0;
	n = 0;
	if (data->num_error != 0 || data->empty_str == YES)
		return ;
	p = getenv("PATH");
	arr_p = ft_split(p, ':');
	while (n < data->num_cmd)
	{
		find_cmd = check_str(data, arr_p, i, n);
		if (find_cmd > 0)
		{
			data->num_error = ERR_CMD;
			printf("\bMimishell: %s: command not found\n",
				data->cmd[n].array_arg[0]);
		}
		n++;
	}
}
