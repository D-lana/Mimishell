#include "minishell.h"

void	ms_record_char(char **result, char *str, int *r, int *s)
{
	(*result)[(*r)] = str[(*s)];
	(*r)++;
	(*s)++;
}

void	ms_record_str(char **file, char *str, int start, int size_str)
{
	int	i;

	i = 0;
	while (i < size_str)
	{
		(*file)[i] = str[start + i];
		i++;
	}
	(*file)[i] = '\0';
}

int	ms_way(t_data *data, int find_cmd, int n)
{
	if (data->cmd[n].array_arg[0][0] == '/')
	{
		data->cmd[n].way_cmd = ft_strdup(data->cmd[n].array_arg[0]);
		if (!access (data->cmd[n].way_cmd, 1))
			find_cmd = -4;
		else
			find_cmd = 0;
	}
	return (find_cmd);
}

int	ms_check_file(t_cmd *cmd, int i)
{
	int		j;
	char	*str;
	char	*str_slesh;
	char	*str_way;
	int		mistake;

	j = 0;
	mistake = 0;
	str = NULL;
	str_way = NULL;
	str_slesh = NULL;
	str = getcwd(NULL, 0);
	str_slesh = ft_strjoin(str, "/");
	str_way = ft_strjoin(str_slesh, cmd->file[i]);
	ms_free_str(&str_slesh);
	if (!access (str_way, 0))
		mistake = 1;
	ms_free_str(&str_way);
	return (mistake);
}

int	ms_err_token(t_data *data, int pipe)
{
	if (pipe == 2)
	{
		data->num_error = ERR_TOKEN;
		data->num_cmd = 0;
		ms_error(data->num_error, "||");
		return (-1);
	}
	data->num_error = ERR_TOKEN;
	data->num_cmd = 0;
	ms_error(data->num_error, "|");
	return (-1);
}
