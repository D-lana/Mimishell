#include "minishell.h"

int	ms_check_quotation_marks(t_cmd *cmd, int i, t_data *data)
{
	char	q_m;

	q_m = cmd->str[i];
	i++;
	while (cmd->str[i] != q_m && cmd->str[i] != '\0')
		i++;
	if (cmd->str[i] == q_m)
		cmd->num_arg++;
	else
	{
		data->num_error = ERR_TOKEN;
		cmd->num_arg = 0;
		return (ms_error(data->num_error, &cmd->str[i - 1]));
	}
	return (i + 1);
}

int	ms_count_args_without_qm(t_cmd *cmd, int i)
{
	if (cmd->str[i] == ' ')
	{
		while (cmd->str[i] == ' ')
			i++;
	}
	if (cmd->str[i] != 39 && cmd->str[i] != 34 && cmd->str[i] != '\0')
		cmd->num_arg++;
	while (cmd->str[i] != 39 && cmd->str[i] != 34 && cmd->str[i] != '\0')
	{
		if (cmd->str[i] == ' ')
		{
			while (cmd->str[i] == ' ' && cmd->str[i] != '\0')
				i++;
			if (cmd->str[i] != 39 && cmd->str[i] != 34 && cmd->str[i] != '\0')
				cmd->num_arg++;
		}
		else
			i++;
	}
	return (i);
}

int	ms_count_arg_divided_qm(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	cmd->num_arg = 0;
	while (cmd->str[i] != '\0')
	{
		if (cmd->str[i] == 34 || cmd->str[i] == 39)
			i = ms_check_quotation_marks(cmd, i, data);
		else
			i = ms_count_args_without_qm(cmd, i);
		if (i == -1)
			return (-1);
	}
	return (0);
}
