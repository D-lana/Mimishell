/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:18:24 by dlana             #+#    #+#             */
/*   Updated: 2022/03/11 16:18:26 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cut_env_variable(t_data *data, int y)
{
	int		i;
	char	**tmp_arr;

	i = 0;
	data->num_env--;
	tmp_arr = data->our_env;
	ms_malloc_array(&data->our_env, data->num_env);
	while (i < y)
	{
		data->our_env[i] = ft_strdup(tmp_arr[i]);
		i++;
	}
	y++;
	while (i < data->num_env)
	{
		data->our_env[i] = ft_strdup(tmp_arr[y]);
		i++;
		y++;
	}
	data->our_env[i] = NULL;
	ms_free_arr(&tmp_arr);
}

void	ms_search_and_delete_env(t_data *data, int i_cmd, int y, int size_key)
{
	int	y_env;

	y_env = 0;
	while (y_env < data->num_env)
	{
		if (ft_strncmp(data->cmd[i_cmd].array_arg[y],
				data->our_env[y_env], size_key) == 0
			&& (data->our_env[y_env][size_key] == '='
			|| data->our_env[y_env][size_key] == '\0'))
		{
			if (ft_strncmp(data->cmd[i_cmd].array_arg[y],
					"OLDPWD=", 6) == 0)
				data->flag_old = 0;
			ms_cut_env_variable(data, y_env);
		}
		y_env++;
	}
}

int	ms_unset(t_data *data, int i_cmd)
{
	int	y;
	int	size_key;

	y = 0;
	size_key = 0;
	while (data->cmd[i_cmd].array_arg[y] != NULL)
	{
		if (ft_isdigit(data->cmd[i_cmd].array_arg[y][0]) == 1)
		{
			data->num_error = ERR_NUM_ONE;
			return (ms_error(data->num_error, data->cmd[i_cmd].array_arg[y]));
		}
		size_key = ft_strlen(data->cmd[i_cmd].array_arg[y]);
		ms_search_and_delete_env(data, i_cmd, y, size_key);
		y++;
	}
	return (0);
}
