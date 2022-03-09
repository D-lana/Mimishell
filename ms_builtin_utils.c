/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:24:54 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/09 18:27:46 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pwd_and_rewrite(t_data *data)
{
	int		i;

	i = 0;
	while(data->our_env[i])
	{
		if ((data->our_env[i][0] == 'P') && (data->our_env[i][1] == 'W')
			&& (data->our_env[i][2] == 'D') && (data->our_env[i][3] == '='))
		{
			ms_free_str(&data->our_env[i]);
			data->our_env[i] = ft_strjoin("PWD=", data->cur_dir);
			break ;
		}
		i++;
	}
}

void	ms_check_oldpwd_rewrite(t_data *data)
{
	int		i;

	i = 0;
	while(data->our_env[i])
	{
		if ((data->our_env[i][0] == 'O') && (data->our_env[i][1] == 'L')
			&& (data->our_env[i][2] == 'D') && (data->our_env[i][3] == 'P')
			&& (data->our_env[i][4] == 'W') && (data->our_env[i][5] == 'D')
			&& (data->our_env[i][6] == '='))
		{
			ms_free_str(&data->our_env[i]);
			data->our_env[i] = ft_strjoin("OLDPWD=", data->prev_dir);
			break ;
		}
		i++;
	}
}