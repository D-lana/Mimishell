/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:09:33 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/11 21:09:36 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free_all(t_data *data, char **line)
{
	if (data->our_env != NULL)
		ms_free_arr(&data->our_env);
	ms_free_cycle(data, line);
	if (data->tmp_var != NULL)
		ms_free_arr(&data->tmp_var);
	ms_free_str(&data->prev_dir);
	ms_free_str(&data->cur_dir);
}

void	ms_free_arg(t_data *data, int y)
{
	int	x;

	x = 0;
	if (data->cmd[y].num_arg > 0)
	{
		while (x < data->cmd[y].num_arg)
		{
			ms_free_str(&data->cmd[y].arg[x].str);
			x++;
		}
		free(data->cmd[y].arg);
		data->cmd[y].arg = NULL;
	}
}

void	ms_free_cycle(t_data *data, char **line)
{
	int	y;

	y = 0;
	ms_free_str(line);
	if (data->num_cmd > 0)
	{
		while (y < data->num_cmd)
		{
			ms_free_arg(data, y);
			if (data->cmd[y].str != NULL)
				ms_free_str(&data->cmd[y].str);
			if (data->cmd[y].array_empty == NO)
				ms_free_arr(&data->cmd[y].array_arg);
			if (data->cmd[y].count_redir > 0)
			{
				ms_free_int_arr(&data->cmd[y].redir);
				ms_free_arr(&data->cmd[y].file);
			}
			if (data->cmd[y].way_cmd != NULL)
				ms_free_str(&data->cmd[y].way_cmd);
			y++;
		}
		free(data->cmd);
		data->cmd = NULL;
	}
}
