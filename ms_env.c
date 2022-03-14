/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:57:08 by dlana             #+#    #+#             */
/*   Updated: 2022/03/14 16:03:28 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env(t_data *data)
{
	int	y;

	y = 0;
	while (y < data->num_env)
	{
		if (ft_strncmp(data->our_env[y], "OLDPWD", 6) == 0)
		{
			if (data->prev_dir != NULL)
			{
				ft_putstr_fd(data->our_env[y], 1);
				write (1, "\n", 1);
			}
		}
		else if (ft_strchr(data->our_env[y], 61) != NULL)
		{
			ft_putstr_fd(data->our_env[y], 1);
			write (1, "\n", 1);
		}
		y++;
	}
}
