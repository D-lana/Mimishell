#include "minishell.h"

void	ms_switch_qm(char c, int *qm_o, int *qm_d)
{
	if (c == DOUBLE_Q_MARK && (*qm_o) == 1)
		(*qm_d) = (*qm_d) * (-1);
	if (c == ONE_Q_MARK && (*qm_d) == 1)
		(*qm_o) = (*qm_o) * (-1);
}

int	ms_cut_quotation_marks(char *str, t_arg *arg, int i)
{
	int		c;
	char	q_m;

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
	printf("alloc str cmd->arg->str\n");
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
	return (i);
}

int	ms_record_args_without_qm(char *str, t_arg *arg, int i, int *num_arg)
{
	int	c;

	c = 0;
	arg->q_m = NO;
	if (str[i] != ' ')
	{
		while (str[i] != 39 && str[i] != 34 && str[i] != '\0' && str[i] != ' ')
		{
			c++;
			i++;
		}
		ms_malloc_str(&arg->str, c);
		printf("alloc str cmd->arg->str\n");
		i = i - c;
		c = 0;
		while (str[i] != 39 && str[i] != 34 && str[i] != '\0' && str[i] != ' ')
			ms_record_char(&arg->str, str, &c, &i);
		arg->str[c] = '\0';
		if (str[i] == ' ')
			arg->space = YES;
		(*num_arg)++;
		return (i);
	}
	return (i + 1);
}

void	ms_create_struct_without_qm(t_cmd *cmd)
{
	int	i;
	int	num_arg;

	i = 0;
	num_arg = 0;
	ms_malloc_arg(&cmd->arg, cmd->num_arg); // free +
	printf("alloc massiv cmd->arg\n");
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
			while (cmd->str[i] != 34 && cmd->str[i] != 39
				&& cmd->str[i] != '\0')
				i = ms_record_args_without_qm(cmd->str,
						&cmd->arg[num_arg], i, &num_arg);
		}
	}
}
