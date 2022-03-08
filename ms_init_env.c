/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:47:21 by dlana             #+#    #+#             */
/*   Updated: 2022/03/08 16:02:58 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_record_lvl(char **str_lvl, char ***env, int y)
{
	int i;
	int num_lvl;
	
	i = 0;
	num_lvl = ft_atoi(*str_lvl);
	num_lvl++;
	ms_free_str(str_lvl);
	*str_lvl = ft_itoa(num_lvl);
	//ms_free_str((*env)[y]);
	//ms_malloc_str((*env)[y], );
	while ((*str_lvl)[i] != '\0')
	{
		(*env)[y][i + 6] = (*str_lvl)[i];
		i++;
	}
	(*env)[y][i + 6] = '\0';
	ms_free_str(str_lvl);
}

int	ms_shell_lvl(char ***env, int y)
{
	char	*str_lvl;
	int		len_str_lvl;
	int		x;
	
	x = 0;
	str_lvl = NULL;
	while ((*env)[y][x] != '\0')
		x++;
	len_str_lvl = x - 6;
	ms_malloc_str(&str_lvl, len_str_lvl);
	x = 0;
	while ((*env)[y][x + 6] != '\0')
	{
		str_lvl[x] = (*env)[y][x + 6];
		x++;
	}
	ms_record_lvl(&str_lvl, env, y);
	return (0);
}

int ms_check_slvl(char **env, int y, int x)
{
	int i;
	
	i = 6;
	while (env[y][i] != '\0')
	{
		if (ft_isdigit(env[y][i]) != 1)
			return (7);
		i++;
	}
	if(env[y][i - 1] == 57)
 		x++;
	return (x);
}

int ms_record_env(t_data *data, char ***env, int y, int shell_lvl)
{
	int x;
	
	x = 0;
	while ((*env)[y][x] != '\0')
		x++;
	if (shell_lvl == YES)
		x = ms_check_slvl(*env, y, x);
	ms_malloc_str(&data->our_env[y], x);
	x = 0;
	while ((*env)[y][x] != '\0')
	{
		if (x == 6 && shell_lvl == YES)
			ms_shell_lvl(env, y);
		data->our_env[y][x] = (*env)[y][x];
		x++;
	}
	data->our_env[y][x] = '\0';
	// if(shell_lvl == YES)
	// {
	// 	write(2, "str_lvl = ", 10);
	// 	ft_putstr_fd(data->our_env[y], 2);
	// 	write(2, "\n", 1);
	// }
	return (0);
}

void	ms_init_env(t_data *data, char ***env)
{
	int	y;
	int shell_lvl;

	y = 0;
	shell_lvl = NO;
	while ((*env)[y] != 0)
		y++;
	data->num_env = y;
	ms_malloc_array(&data->our_env, y);
	y = 0;
	while ((*env)[y] != 0)
	{
		if(ft_strncmp((*env)[y], "SHLVL=", 6) == 0)
			shell_lvl = YES;
		ms_record_env(data, env, y, shell_lvl);
		shell_lvl = NO;
		y++;
	}
	data->our_env[y] = NULL;
	//ms_print_env(data);
}