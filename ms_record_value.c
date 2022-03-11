/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_record_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:19:01 by dlana             #+#    #+#             */
/*   Updated: 2022/03/11 18:14:52 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_record_tail(char **tmp, char **str, int t, int start_tail)
{
	int	s;

	s = 0;
	while ((*str)[s] != '\0')
	{
		if (s >= start_tail)
		{
			(*tmp)[t] = (*str)[s];
			t++;
		}
		s++;
	}
	(*tmp)[t] = '\0';
	ms_free_str(str);
	*str = ft_strdup((*tmp));
	ms_free_str(tmp);
}

void	ms_replase_key_to_value(char **str, int key, char *value, int start)
{
	int		s;
	int		t;
	char	*tmp;
	int		size;

	s = 0;
	t = 0;
	size = ft_strlen(*str) + ft_strlen(value) - key;
	if (size <= 0)
	{
		ms_free_str(str);
		ms_malloc_str(str, 0);
		(*str)[0] = '\0';
		return ;
	}
	ms_malloc_str(&tmp, size);
	while (s < start)
		ms_record_char(&tmp, (*str), &t, &s);
	s = 0;
	if (value != NULL)
	{
		while (value[s] != '\0')
			ms_record_char(&tmp, value, &t, &s);
	}
	ms_record_tail(&tmp, str, t, start + key);
}

int	ms_record_key(char *s, int i, char **key, int *digit_key)
{
	int	n;

	n = 0;
	if (ft_isdigit(s[i]) == 1)
	{
		(*key) = "1\0";
		(*digit_key) = YES;
		return (1);
	}
	while (s[i] != '\0' && s[i] != ' ' && s[i] != 34
		&& s[i] != '$' && s[i] != ONE_Q_MARK && s[i] != '=')
	{
		i++;
		n++;
	}
	ms_malloc_str(key, n);
	i = (i - n);
	n = 0;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != 34
		&& s[i] != '$' && s[i] != ONE_Q_MARK && s[i] != '=')
		ms_record_char(key, s, &n, &i);
	(*key)[n] = '\0';
	return (n);
}

int	ms_search_var(t_data *data, char **value, char *key)
{
	int	y;
	int	size_key;
	int	start;

	y = 0;
	size_key = ft_strlen(key);
	start = ft_strlen(key) + 1;
	while (y < data->num_env)
	{
		if (ft_strncmp(key, data->our_env[y], size_key) == 0
			&& (data->our_env[y][size_key] == '='
			|| data->our_env[y][size_key] == '\0'))
		{
			(*value) = ft_strdup_start(data->our_env[y], start);
			return (0);
		}
		y++;
	}
	return (-1);
}

int	ms_record_value(t_data *data, char **str, int i)
{
	int		n;
	char	*key;
	char	*value;
	int		digit_key;

	i++;
	n = 1;
	digit_key = NO;
	value = NULL;
	n = ms_record_key(*str, i, &key, &digit_key);
	if (digit_key == NO)
	{
		ms_search_var(data, &value, key);
		ms_free_str(&key);
	}
	if (value == NULL && data->name_file == YES)
		return (i);
	ms_replase_key_to_value(str, 1, NULL, (i - 1));
	ms_replase_key_to_value(str, n, value, (i - 1));
	ms_free_str(&value);
	return (i);
}
