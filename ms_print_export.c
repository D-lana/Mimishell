/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:54:56 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/11 20:56:03 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_print_sort_export(t_data *data, int y)
{
	int		x;
	char	qm_d;

	x = 0;
	qm_d = DOUBLE_Q_MARK;
	write(1, "declare -x ", 12);
	while (data->our_env[y][x] != '=' && data->our_env[y][x] != '\0')
	{
		write(1, &data->our_env[y][x], 1);
		x++;
	}
	if (data->our_env[y][x] != '\0')
	{
		write(1, "=", 1);
		x++;
		write(1, &qm_d, 1);
		while (data->our_env[y][x] != '\0')
		{
			write(1, &data->our_env[y][x], 1);
			x++;
		}
		write(1, &qm_d, 1);
	}
	write(1, "\n", 1);
}
