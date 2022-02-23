/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:47:21 by dlana             #+#    #+#             */
/*   Updated: 2022/02/23 17:42:56 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ms_create_points(t_data *data, int y)
// {
// 	if(y == 0)
// 	{
// 		data->env[y].next = &data->env[data->num_env];
// 		data->env[y].prev = &data->env[y + 1];
// 	}
// 	else if (y == data->num_env)
// 	{
// 		data->env[y].next = &data->env[y - 1];
// 		data->env[y].prev = &data->env[0];
// 	}
// 	else
// 	{
// 		data->env[y].next = &data->env[y - 1];
// 		data->env[y].prev = &data->env[y + 1];
// 	}
// }

// void	ms_record_env(t_data *data, char **env, int y)
// {
// 	int	x_k;
// 	int	x_v;

// 	x_k = 0;
// 	x_v = 0;
// 	t_env *tmp;
// 	tmp = malloc(sizeof(t_env));
// 	data->env[y] = *tmp;
// 	while (env[y][x_k] != '=' && env[y][x_k] != '\0')
// 		x_k++;
// 	ms_malloc_str(&data->env[y].key, x_k);
// 	ms_record_str(&data->env[y].key, env[y], 0, x_k);
// 	if (env[y][x_k] != '\0')
// 	{
// 		x_v = x_k + 1;
// 		while (env[y][x_v] != '\0')
// 			x_v++;
// 		ms_malloc_str(&data->env[y].value, (x_v - x_k - 1));
// 		ms_record_str(&data->env[y].value, env[y], (x_k + 1), (x_v - x_k - 1));
// 	}
// 	ms_create_points(data, y);
	
// }

// void	ms_record_env(t_data *data, char **env, int y)
// {
// 	int	x_k;
// 	int	x_v;

// 	x_k = 0;
// 	x_v = 0;
// 	t_env *tmp;
// 	char *tmp_key = NULL;
// 	char *tmp_value = NULL;
// 	tmp = malloc(sizeof(t_env));
// 	//printf("here\n");
// 	ms_malloc_env(&tmp, 0);
// 	while (env[y][x_k] != '=' && env[y][x_k] != '\0')
// 		x_k++;
// 	ms_malloc_str(&tmp_key, x_k);
// 	ms_record_str(&tmp_key, env[y], 0, x_k);
// 	if (env[y][x_k] == '=')
// 	{
// 		x_v = x_k + 1;
// 		while (env[y][x_v] != '\0')
// 			x_v++;
// 		ms_malloc_str(&tmp_value, (x_v - x_k - 1));
// 		ms_record_str(&tmp_value, env[y], (x_k + 1), (x_v - x_k - 1));
// 	}
// 	tmp->key = tmp_key;
// 	tmp->value = tmp_value;
// 	if (data->env == 0)
// 	{
// 		tmp->prev = tmp;
// 		tmp->next = tmp;
// 	}
// 	if (data->env != 0)
// 	{
// 		tmp->prev = data->env->prev;
// 		data->env->prev->next = tmp;
// 		tmp->next = data->env;
// 		data->env->prev = tmp;
// 	}
// 	// ms_create_points(data, y);
// 	data->env = tmp;
// }

// void	ft_create_env_list(t_env *env, char *key, char *value)
// {
// 	t_env	*tmp;

// 	tmp = malloc(sizeof(t_env));
// 	if (!tmp)
// 		ft_error();
// 	tmp->key = key;
// 	tmp->value = value;
// 	if (env == 0)
// 	{
// 		tmp->prev = tmp;
// 		tmp->next = tmp;
// 	}
// 	if (env != 0)
// 	{
// 		tmp->prev = env->prev;
// 		env->prev->next = tmp;
// 		tmp->next = env;
// 		env->prev = tmp;
// 	}
// 	env = tmp;
// }

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
	data->env = 0;
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