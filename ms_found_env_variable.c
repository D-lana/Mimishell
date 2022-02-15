#include "minishell.h"

int	ms_found_env_variable(int err, t_cmd *cmd);
void ms_replase_key_to_value(char **str, char *key, const char *value, int start);
void ms_record_value(t_cmd *cmd, int *i, int num_arg);
void ms_put_error(int err, char **str, int *start);


void ms_put_error(int err, char **str, int *start)
{
	int i;

	i = *start;
	char *str_err;
	str_err = ft_itoa(err);
	ms_replase_key_to_value(str, "$?", str_err, i);
	ms_free_str(&str_err);
	(*start) += 2;
}

int	ms_found_env_variable(int err, t_cmd *cmd)
{
	int			i;
	int 		num_arg;

	i = 0;
	num_arg = 0;
	while (num_arg < cmd->num_arg)
	{
		while (cmd->arg[num_arg].str[i] != '\0')
		{
			if (cmd->arg[num_arg].str[i] == '$' && cmd->arg[num_arg].str[i + 1] == '$')
				i += 2;//ms_record_ps(&cmd->arg[num_arg].str, &i);//////////////////////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			else if (cmd->arg[num_arg].str[i] == '$' && cmd->arg[num_arg].str[i + 1] == '?')
				ms_put_error(err, &cmd->arg[num_arg].str, &i);
			else if (cmd->arg[num_arg].str[i] == '$' && cmd->arg[num_arg].q_m != ONE_Q_MARK
				&& (cmd->arg[num_arg].str[i + 1] != '\0' && cmd->arg[num_arg].str[i + 1] != ' '))
				ms_record_value(cmd, &i, num_arg);
			else
				i++;
		}
		num_arg++;
		i = 0;
	}
	return (0);
}

void ms_replase_key_to_value(char **str, char *key, const char *value, int start)
{
	int i;
	int v;
	int new_size;
	int size_key;
	char	*tmp;

	i = 0;
	v = 0;
	size_key = (ft_strlen(key)) - ft_strlen(value);
	new_size = ft_strlen(*str) - (ft_strlen(key)) + ft_strlen(value);
	tmp = (*str);
	ms_malloc_str(str, new_size);
	while (i < start)
	{
		(*str)[i] = tmp[i];
		i++;
	}
	if (ft_strlen(value) > 0)
	{
		while (value[v] !=  '\0')
			ms_record_char(str, value, &i, &v);
	}
	//printf("ir=%d\n", i);
	//printf("size_key=%d\n", size_key);
	if (i + size_key >= 0)
	{
		while (tmp[i + size_key] != '\0')
		{
			(*str)[i] = tmp[i + size_key];
			i++;
		}
	}
	//printf("ir=%d\n", i);
	(*str)[i] = '\0';
	ms_free_str(&tmp);
}

void ms_record_value(t_cmd *cmd, int *i, int num_arg)
{
	int	n;
	char		*key;
	const char	*value;
	char		*s;

	n = 0;
	(*i)++;
	s = cmd->arg[num_arg].str;
	if (ft_isdigit(s[(*i)]) == 1)
		key = "1\0";
	else
	{
		while(s[(*i)] != '\0' && s[(*i)] != ' ' && s[(*i)] != '$' && s[(*i)] != ONE_Q_MARK)
		{
			(*i)++;
			n++;
		}
		ms_malloc_str(&key, n);
		(*i) = (*i - n);
		n = 0;
		while(s[(*i)] != '\0' && s[(*i)] != ' ' && s[(*i)] != '$' && s[(*i)] != ONE_Q_MARK)
			 ms_record_char(&key, s, &n, i);
		key[n] = '\0';
	}
	value = getenv(key);
	ms_replase_key_to_value(&cmd->arg[num_arg].str, "$", NULL, (*i - n - 1));
	ms_replase_key_to_value(&cmd->arg[num_arg].str, key, value, (*i - n - 1));
	//printf("value = %s\n", value);
	//printf("key_name = %s\n", key);
	//printf("i=%d\n", (*i));
}

// void ms_record_ps(char **str, int *i)
// {
// 	ms_replase_key_to_value(str, "$$", "number", (*i));
// 	(*i) += 2;
// 	//printf("i=%d\n", (*i));
// }
