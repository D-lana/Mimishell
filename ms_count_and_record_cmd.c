/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_count_and_record_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:05:51 by dlana             #+#    #+#             */
/*   Updated: 2022/03/13 20:24:55 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_get_size_one_cmd_str(char *line, int *start, int size)
{
	int	i;
	int	qm_d;
	int	qm_o;

	i = 0;
	qm_o = 1;
	qm_d = 1;
	while (line[(*start) + size] != '\0')
	{
		ms_switch_qm(line[(*start) + size], &qm_o, &qm_d);
		if (line[(*start) + size] == '|' && qm_o == 1 && qm_d == 1)
			break ;
		size++;
	}
	return (size);
}

int	ms_record_one_str(char **str, char *line, int *start, int *num)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	size = ms_get_size_one_cmd_str(line, start, size);
	ms_malloc_str(str, size);
	while (i < size)
	{
		(*str)[i] = line[(*start) + i];
		i++;
	}
	(*str)[i] = '\0';
	(*num)++;
	if (line[(*start) + i] == '|')
		i++;
	(*start) = (*start) + i;
	return (0);
}

static int	ms_count_pipe(t_data *data, char *line, int qm_d, int qm_o)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		ms_switch_qm(line[i], &qm_o, &qm_d);
		if (line[i] == '|' && qm_o == 1 && qm_d == 1)
		{
			i++;
			if (line[i] == '|')
				return (ms_err_token(data, 2));
			if (line[i] == ' ')
			{
				while (line[i] == ' ' && line[i] != '\0')
					i++;
			}
			if (line[i] == '\0' || line[i] == '|')
				return (ms_err_token(data, 1));
			data->num_cmd++;
		}
		i++;
	}
	return (0);
}

int	ms_check_empty_and_err_token_pipe(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
	{
		data->empty_str = YES;
		return (-1);
	}
	if (line[i] == '|')
	{
		data->num_error = ERR_TOKEN;
		data->num_cmd = 0;
		if (line[i + 1] == '|')
			return (ms_error(data->num_error, "||"));
		return (ms_error(data->num_error, "|"));
	}
	return (0);
}

int	ms_count_and_record_cmd(t_data *data, char *line)
{
	int	i;
	int	num;
	int	qm_d;
	int	qm_o;

	i = 0;
	qm_o = 1;
	qm_d = 1;
	data->num_cmd = 1;
	if (ms_check_empty_and_err_token_pipe(data, line) == -1)
		return (-1);
	if (ms_count_pipe(data, line, 1, 1) == -1)
		return (-1);
	ms_malloc_cmd(&data->cmd, data->num_cmd);
	i = 0;
	while (data->num_cmd > i)
	{
		data->cmd[i] = (t_cmd){};
		i++;
	}
	i = 0;
	num = 0;
	while (line[i] != '\0')
		ms_record_one_str(&data->cmd[num].str, line, &i, &num);
	return (0);
}
