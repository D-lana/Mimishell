/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_found_env_variable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:51:48 by dlana             #+#    #+#             */
/*   Updated: 2022/03/09 20:48:49 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_put_num_error(int err, char **str, int *start)
{
	int		i;
	char	*str_err;

	i = *start;
	str_err = ft_itoa(err);
	ms_replase_key_to_value(str, 2, str_err, i);
	ms_free_str(&str_err);
	(*start)++;
}

void	ms_found_dollar(t_data *data, char **str, int q_m, int *i_orig)
{
	int i;

	i = (*i_orig);
	if ((*str)[i] == '$' && (*str)[i + 1] == '$')
		i += 2;
	else if ((*str)[i] == '$' && (*str)[i + 1] == '?')
		ms_put_num_error(data->num_prev_error, str, &i);
	else if ((*str)[i] == '$' && (*str)[i + 1] != ' '
		&& ((*str)[i + 1] != '\0' && q_m != 39))
	{
		i++;
		ms_record_value(data, str, i);
		if ((*str)[0] == '\0')
			return ;
	}
	else
		i++;
	(*i_orig) = i;
}

int	ms_found_env_variable(t_data *data, t_cmd *cmd)
{
	int	y;
	int	i;

	i = 0;
	y = 0;
	while (y < cmd->num_arg)
	{
		cmd->arg[y].empty_key = NO;
		while (cmd->arg[y].str[i] != '\0')
			ms_found_dollar(data, &cmd->arg[y].str, cmd->arg[y].q_m, &i);
		if (ft_strlen(cmd->arg[y].str) == 0)
			cmd->arg[y].empty_key = YES;
		y++;
		i = 0;
		
	}
	return (0);
}
