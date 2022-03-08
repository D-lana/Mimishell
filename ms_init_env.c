/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:47:21 by dlana             #+#    #+#             */
/*   Updated: 2022/03/08 13:37:55 by obeedril         ###   ########.fr       */
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
void	ms_record_lvl(t_data *data, char **str_lvl, int y)
{
	int x;
	int num_lvl;
	
	x = 0;
	num_lvl = ft_atoi(*str_lvl);
	num_lvl++;
	ms_free_str(str_lvl);
	*str_lvl = ft_itoa(num_lvl);
	while ((*str_lvl)[x] != '\0')
	{
		data->our_env[y][6 + x] = (*str_lvl)[x];
		x++;
	}
	data->our_env[y][x] = '\0';
	free((*str_lvl));
}

int	ms_shell_lvl(t_data *data, char **env, int y)
{
	char *str_lvl;
	int x;
	
	x = 0;
	str_lvl = NULL;
	while (env[y][x] != '\0')
		x++;
	ms_malloc_str(&str_lvl, x - 6);
	if (env[y][x - 1] == 9 + '0')
		x++;
	ms_malloc_str(&data->our_env[y], x);
	x = 0;
	while (env[y][x] != '\0' && x < 6)
	{
		data->our_env[y][x] = env[y][x];
		x++;
	}
	ms_record_lvl(data, &str_lvl, y);
	return (0);
}

int ms_record_env(t_data *data, char **env, int y, int shell_lvl)
{
	int x;
	
	x = 0;
	while (env[y][x] != '\0')
		x++;
	if(shell_lvl == YES)
		return (ms_shell_lvl(data, env, y));
	ms_malloc_str(&data->our_env[y], x);
	x = 0;
	while (env[y][x] != '\0')
	{
		data->our_env[y][x] = env[y][x];
		x++;
	}
	data->our_env[y][x] = '\0';
	return (0);
}

void	ms_init_env(t_data *data, char **env)
{
	int	y;
	int shell_lvl;

	y = 0;
	shell_lvl = NO;
	while (env[y] != 0)
		y++;
	data->num_env = y;
	ms_malloc_array(&data->our_env, y);
	y = 0;
	while (env[y] != 0)
	{
		if(ft_strncmp(env[y], "SHLVL=", 6) == 0)
			shell_lvl = YES;
		ms_record_env(data, env, y, shell_lvl);
		shell_lvl = NO;
		y++;
	}
	data->our_env[y] = NULL;
	//ms_print_env(data);
}