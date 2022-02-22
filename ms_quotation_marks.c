#include "minishell.h"

void ms_switch_qm(char *s, int i, int *qm_o, int *qm_d)
{
	if (s[i] == DOUBLE_Q_MARK && (*qm_o) == 1)
		(*qm_d) = (*qm_d) * (-1);
	if (s[i] == ONE_Q_MARK &&  (*qm_d) == 1)
		(*qm_o) = (*qm_o) * (-1);
}

int	ms_cut_quotation_marks(char *str, t_arg *arg, int i)
{
	int c;
	char q_m;

	c = 0;
	q_m = str[i];
	i++;
	arg->q_m = (int)q_m;
	while (str[i] != q_m && str[i] != '\0') 
	{
		c++;
		i++;
	}
	ms_malloc_str(&arg->str, c);
	i = i - c;
	c = 0;
	while (str[i] != q_m && str[i] != '\0')
		ms_record_char(&arg->str, str, &c, &i);
	if (str[i] == q_m)
	{
		i++;
		if (str[i] == ' ')
			arg->space = YES;
	}
	arg->str[c] = '\0';
	return(i); //// +1
}

int	ms_record_args_without_qm(char *str, t_arg *arg, int i)
{
	int c = 0;
	arg->q_m = NO;
	while (str[i] != 39 && str[i] != 34 && str[i] != '\0' && str[i] != ' ')
	{
		c++;
		i++;
	}
	ms_malloc_str(&arg->str, c);
	i = i - c;
	c = 0;
	while (str[i] != 39 && str[i] != 34 && str[i] != '\0' && str[i] != ' ')
		ms_record_char(&arg->str, str, &c, &i); // printf("%c", arg->str[c] = str[i]);
	arg->str[c] = '\0';
	if (str[i] == ' ')
		arg->space = YES;
	return (i);
}

void	ms_create_struct_without_qm(t_cmd *cmd) 
{
	int	i;
	int num_arg;

	i = 0;
	num_arg = 0;
	ms_malloc_arg(&cmd->arg, cmd->num_arg);
	while (cmd->str[i] != '\0')
	{
		cmd->arg[num_arg].space = NO;
		cmd->arg[num_arg].empty_key = NO;
		if (cmd->str[i] == 34 || cmd->str[i] == 39)
		{
			i = ms_cut_quotation_marks(cmd->str, &cmd->arg[num_arg], i);
			num_arg++;
		}
		else
		{
			while (cmd->str[i] != 34 && cmd->str[i] != 39 && cmd->str[i] != '\0')
			{
				if (cmd->str[i] != ' ')
				{
					i = ms_record_args_without_qm(cmd->str, &cmd->arg[num_arg], i);
					num_arg++;
				}
				else 
					i++;
			}
		}
	}
}

int ms_check_quotation_marks(t_cmd *cmd, int i, t_data *data)
{
	char q_m;

	q_m = cmd->str[i];
	i++;
	while (cmd->str[i] != q_m && cmd->str[i] != '\0')
		i++;
	if (cmd->str[i] == q_m)
		cmd->num_arg++;
	else
	{
		data->num_error = ERR_TOKEN;
		return((ms_error(&data->num_error, &cmd->str[i - 1])));
	}
	return (i + 1);
}

int ms_count_args_without_qm(t_cmd *cmd, int i)
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
			while (cmd->str[i] == ' ' && cmd->str[i] != '\0')///////////////////////
				i++;
			if (cmd->str[i] != 39 && cmd->str[i] != 34 && cmd->str[i] != '\0')
				cmd->num_arg++;
		}
		else
			i++; //printf("%c", cmd->str[i]);
	}
	return(i);
}

int ms_count_arg_divided_qm(t_cmd *cmd, t_data *data)
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
