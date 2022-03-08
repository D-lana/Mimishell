/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_found_env_variable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:51:48 by dlana             #+#    #+#             */
/*   Updated: 2022/03/08 12:22:14 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_replase_key_to_value(char **str, int key, char *value, int start)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = (*str);
	ms_malloc_str(str, (ft_strlen(*str) - key + ft_strlen(value)));
	while (i < start)
		ms_record_char(str, tmp, &i, &j);
	j = 0;
	if (ft_strlen(value) > 0)
	{
		while (value[j] != '\0')
			ms_record_char(str, value, &i, &j);
	}
	j = i + (key - ft_strlen(value));
	if (j >= 0)
	{
		while (tmp[j] != '\0')
			ms_record_char(str, tmp, &i, &j);
	}
	(*str)[i] = '\0';
	ms_free_str((char **)&tmp);
}

int	ms_record_key(char *s, int *i, char **key)
{
	int		n;

	n = 0;
	while (s[(*i)] != '\0' && s[(*i)] != ' ' && s[(*i)] != 34
		&& s[(*i)] != '$' && s[(*i)] != ONE_Q_MARK )
	{
		(*i)++;
		n++;
	}
	ms_malloc_str(key, n);
	(*i) = (*i - n);
	n = 0;
	while (s[(*i)] != '\0' && s[(*i)] != ' ' && s[(*i)] != 34
		&& s[(*i)] != '$' && s[(*i)] != ONE_Q_MARK)
		ms_record_char(key, s, &n, i);
	(*key)[n] = '\0';
	return (n);
}

int	ms_record_value(t_data *data, char **str, int i)
{
	int		n;
	char	*key;
	char	*value;
	int		i_dup;

	n = 0;
	i_dup = i;
	i++;
	if (ft_isdigit((*str)[i]) == 1)
		key = "1\0";
	else
		n = ms_record_key(*str, &i, &key);
	value = getenv(key);
	if (value == NULL && data->name_file == YES)
		return (i_dup + 1);
	ms_replase_key_to_value(str, 1, NULL, (i - n - 1));
	ms_replase_key_to_value(str, n, value, (i - n - 1));
	return (i_dup);
}

void	ms_put_num_error(int err, char **str, int *start)
{
	int		i;
	char	*str_err;

	i = *start;
	str_err = ft_itoa(err);
	ms_replase_key_to_value(str, 2, str_err, i);
	ms_free_str(&str_err);
	(*start) += 2;
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
		i = ms_record_value(data, str, i);
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
