/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:27:28 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/11 21:47:48 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_check_name(t_data *data, int i)
{
	int	j;

	j = 0;
	if (data->cmd[i].count_redir != 0)
	{
		while (data->cmd[i].file[j])
		{
			if (data->cmd[i].file[j][0] == '/')
			{
				if (opendir(data->cmd[i].file[j]) != 0)
				{
					data->num_error = ERR_FILE_OR_DIR;
					ms_print_errors_chfa(data->cmd[i].file[j], 2);
					return (-1);
				}
			}
			j++;
		}
	}
	return (0);
}
