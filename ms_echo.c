/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:23:17 by dlana             #+#    #+#             */
/*   Updated: 2022/03/13 16:29:05 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_found_minus_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '\0')
		return (-1);
	if (arg[i] != '-' || arg[i + 1] != 'n')
		return (-1);
	i++;
	while (arg[i] == 'n' && arg[i] != '\0')
		i++;
	if (arg[i] != '\0')
		return (-1);
	return (0);
}

int ms_echo_print(t_data *data, int i, int *n, int j)
{
    if (data->n_end == 0 && ms_found_minus_n(data->cmd[i].array_arg[j]) == 0)
    {
        (*n) = YES;
        j++;
    }
    else
    {
		data->n_end = YES;
		if (ft_strncmp(data->cmd[i].array_arg[j], "~\0", 2) == 0)
			ft_putstr_fd(data->home_dir, 1);
		else
			ft_putstr_fd(data->cmd[i].array_arg[j], 1);
		j++;
    }
    if (j < data->cmd[i].num_array_arg && data->n_end == YES)
        write(1, " ", 1);
    return (j);
}
void    ms_echo(t_data *data, int i)
{
    int j;
    int n;
    j = 1;
    n = NO;
    data->n_end = 0;
    while (j < data->cmd[i].num_array_arg)
        j = ms_echo_print(data, i, &n, j);
    if (n != YES)
	{
		 write(1, "\n", 1);
	}
}
