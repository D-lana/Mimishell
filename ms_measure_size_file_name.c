/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_measure_size_file_name.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:51:47 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/11 20:51:50 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_err_name_file(t_data *data, int qm_o, int qm_d)
{
	char	qmd[2];

	qmd[0] = DOUBLE_Q_MARK;
	qmd[1] = '\0';
	data->num_error = ERR_TOKEN;
	if (qm_o != 1)
		ms_error(ERR_TOKEN, "'");
	else if (qm_d != 1)
		ms_error(ERR_TOKEN, qmd);
	return (-1);
}

int	ms_measure_size_file_name(t_data *d, char *str, int *i)
{
	int	qm_o;
	int	qm_d;
	int	size_str;

	size_str = 0;
	qm_o = 1;
	qm_d = 1;
	while (str[(*i)] != '\0')
	{
		ms_switch_qm(str[(*i)], &qm_o, &qm_d);
		if (str[(*i)] == ' ' && qm_o == 1 && qm_d == 1)
			break ;
		size_str++;
		(*i)++;
	}
	if (qm_o != 1 || qm_d != 1)
		return (ms_err_name_file(d, qm_o, qm_d));
	return (size_str);
}
