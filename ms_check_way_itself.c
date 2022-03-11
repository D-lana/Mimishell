/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_way_itself.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:04:37 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/11 20:19:29 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_find_cmd(t_data *data, int n, int find_cmd, char *str_way)
{
	if (opendir(data->cmd[n].array_arg[0]) != 0)
		find_cmd = -2;
	else if (!access (str_way, 1))
	{
		find_cmd = -1;
		data->cmd[n].way_cmd = ft_strdup(str_way);
	}
	else
	{
		if (!access (str_way, 0))
			find_cmd = -3;
		else
			find_cmd = 0;
	}
	ms_free_str(&str_way);
	return (find_cmd);
}

int	ms_check_way_itself(t_data *data, int find_cmd, int n)
{
	char	*str;
	char	*str_slesh;
	char	*str_way;

	str = NULL;
	str_way = NULL;
	str_slesh = NULL;
	str = getcwd(NULL, 0);
	str_slesh = ft_strjoin(str, "/");
	ms_free_str(&str);
	str_way = ft_strjoin(str_slesh, data->cmd[n].array_arg[0]);
	ms_free_str(&str_slesh);
	find_cmd = ms_find_cmd(data, n, find_cmd, str_way);
	return (find_cmd);
}
