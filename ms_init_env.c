/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:47:21 by dlana             #+#    #+#             */
/*   Updated: 2022/02/26 16:27:00 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void ms_print_env(t_data *data)
// {
// 	int	y;

// 	y = 0;
// 	while (y < data->num_env)
// 	{
// 		printf("%s\n", data->our_env[y]);
// 		//printf("%s=", data->env->key);
// 		//printf("%s\n", data->env->value);
// 		//data->env = data->env->next;
// 		y++;
// 	}
// }

void ms_record_env(t_data *data, char **env, int y)
{
	int x;

	x = 0;
	while (env[y][x] != '\0')
		x++;
	ms_malloc_str(&data->our_env[y], x);
	x = 0;
	while (env[y][x] != '\0')
	{
		data->our_env[y][x] = env[y][x];
		x++;
	}
	data->our_env[y][x] = '\0';
}

void	ms_init_env(t_data *data, char **env)
{
	int	y;

	y = 0;
	
	while (env[y] != 0)
		y++;
	data->num_env = y;
	ms_malloc_array(&data->our_env, y);
	y = 0;
	while (env[y] != 0)
	{
		ms_record_env(data, env, y);
		y++;
	}
	data->our_env[y] = NULL;
	//ms_print_env(data);
}