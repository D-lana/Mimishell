/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:00:01 by dlana             #+#    #+#             */
/*   Updated: 2022/03/13 19:45:23 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_replace_value(t_data *data, int y, char **var, int x)
{
	char	*tmp;

	tmp = data->our_env[y];
	if ((*var)[x] == '=')
	{
		ms_free_str(&data->our_env[y]);
		data->our_env[y] = ft_strdup((*var));
	}
	else if ((*var)[x] == '+')
	{
		ms_replase_key_to_value(var, x + 2, NULL, 0);
		data->our_env[y] = ft_strjoin(data->our_env[y], (*var));
		ms_free_str(&tmp);
	}
}

void	ms_add_new_variable(t_data *data, char **var)
{
	int		i;
	char	**tmp_arr;

	i = 0;
	data->num_env++;
	tmp_arr = data->our_env;
	ms_malloc_array(&data->our_env, data->num_env);
	while (i < data->num_env - 1)
	{
		data->our_env[i] = ft_strdup(tmp_arr[i]);
		i++;
	}
	data->our_env[i] = ft_strdup((*var));
	i++;
	data->our_env[i] = NULL;
	ms_free_arr(&tmp_arr);
}

void	ms_add_var(t_data *data, char **var)
{
	int	x;
	int	y;
	int	new_key;

	x = 0;
	y = 0;
	new_key = YES;
	while ((*var)[x] != '\0' && (*var)[x] != '=' && (*var)[x] != '+')
		x++;
	ms_found_tmp_var(data, var, x);
	while (y < data->num_env)
	{
		if (ft_strncmp((*var), data->our_env[y], x) == 0
			&& (data->our_env[y][x] == '=' || data->our_env[y][x] == '\0'))
		{
			ms_replace_value(data, y, var, x);
			new_key = NO;
		}
		y++;
	}
	if (new_key == YES)
		ms_add_new_variable(data, var);
}

int	ms_valid_export(char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[i]) == 1 || var[i] == '=')
		return (ERR_NUM_ONE);
	while (var[i] != '\0')
	{
		if (var[i] == '=' || (var[i] == '+' && var[i + 1] == '='))
			break ;
		else if (ft_isalpha(var[i]) != 1 && ft_isdigit(var[i]) != 1
			&& var[i] != 95)
			return (ERR_NUM_ONE);
		i++;
	}
	if (var[i] == '+' && var[i + 1] == '=' && i > 0)
		return (ADD_TO_OLD);
	else if (var[i] == '=' && i > 0)
		return (ADD_NEW);
	return (0);
}

int	ms_add_env_variable(t_data *data, int i_cmd)
{
	int	i;
	int	valid;

	i = 1;
	valid = 0;
	while (data->cmd[i_cmd].array_arg[i] != NULL)
	{
		valid = ms_valid_export(data->cmd[i_cmd].array_arg[i]);
		if (valid == ERR_NUM_ONE)
		{
			data->num_error = ERR_NUM_ONE;
			ms_err_export(data->num_error,
				data->cmd[i_cmd].array_arg[i], "export\0");
		}
		else
			ms_add_var(data, &data->cmd[i_cmd].array_arg[i]);
		i++;
	}
	return (0);
}
