/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_found_env_variable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:51:48 by dlana             #+#    #+#             */
/*   Updated: 2022/02/22 14:16:14 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ms_found_env_variable(int err, t_cmd *cmd);
void	ms_replase_key_to_value(char **str, int key, char *value, int start);
void	ms_record_value(t_cmd *cmd, int *i, int num_arg);
void	ms_put_num_error(int err, char **str, int *start);
int		ms_record_key(t_cmd *cmd, int *i, int num_arg, char **key);

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

int	ms_found_env_variable(int err, t_cmd *cmd)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (y < cmd->num_arg)
	{
		while (cmd->arg[y].str[i] != '\0')
		{
			if (cmd->arg[y].str[i] == '$' && cmd->arg[y].str[i + 1] == '$')
				i += 2;
			else if (cmd->arg[y].str[i] == '$' && cmd->arg[y].str[i + 1] == '?')
				ms_put_num_error(err, &cmd->arg[y].str, &i);
			else if (cmd->arg[y].str[i] == '$' && cmd->arg[y].str[i + 1] != ' '
				&& (cmd->arg[y].str[i + 1] != '\0' && cmd->arg[y].q_m != 39))
				ms_record_value(cmd, &i, y);
			else
				i++;
		}
		y++;
		i = 0;
	}
	return (0);
}

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

int	ms_record_key(t_cmd *cmd, int *i, int num_arg, char **key)
{
	char	*s;
	int		n;

	n = 0;
	s = cmd->arg[num_arg].str;
	while (s[(*i)] != '\0' && s[(*i)] != ' '
		&& s[(*i)] != '$' && s[(*i)] != ONE_Q_MARK)
	{
		(*i)++;
		n++;
	}
	ms_malloc_str(key, n);
	(*i) = (*i - n);
	n = 0;
	while (s[(*i)] != '\0' && s[(*i)] != ' '
		&& s[(*i)] != '$' && s[(*i)] != ONE_Q_MARK)
		ms_record_char(key, cmd->arg[num_arg].str, &n, i);
	(*key)[n] = '\0';
	return (n);
}

void	ms_record_value(t_cmd *cmd, int *i, int num_arg)
{
	int		n;
	char	*key;
	char	*value;

	n = 0;
	cmd->arg[num_arg].empty_key = NO;
	(*i)++;
	if (ft_isdigit(cmd->arg[num_arg].str[(*i)]) == 1)
		key = "1\0";
	else
		n = ms_record_key(cmd, i, num_arg, &key);
	value = getenv(key);
	ms_replase_key_to_value(&cmd->arg[num_arg].str, 1, NULL, (*i - n - 1));
	ms_replase_key_to_value(&cmd->arg[num_arg].str, n, value, (*i - n - 1));
	// ms_replase_key_to_value(&cmd->arg[num_arg].str, "$", NULL, (*i - n - 1));
	// ms_replase_key_to_value(&cmd->arg[num_arg].str, key, value, (*i - n - 1));
	if (ft_strlen(cmd->arg[num_arg].str) == 0)
		cmd->arg[num_arg].empty_key = YES;
}
