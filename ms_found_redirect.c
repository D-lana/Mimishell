#include "minishell.h"

int	ms_error_parse_redir(t_data *data, char *s, int i)
{
	if (s[i] == '>' || s[i] == '<' || s[i] == '\0')
	{
		data->num_error = ERR_TOKEN;
		if (s[i] == '\0')
			ms_error(data->num_error, "newline");
		if (s[i] == '>')
		{
			if (s[i + 1] == '>')
				ms_error(data->num_error, ">>");
			else
				ms_error(data->num_error, ">");
		}
		if (s[i] == '<')
		{
			if (s[i + 1] == '<')
				ms_error(data->num_error, "<<");
			else if (s[i + 1] == '>')
				ms_error(data->num_error, "<>");
			else
				ms_error(data->num_error, "<");
		}
		return (-1);
	}
	return (0);
}

int	ms_count_redirect(t_cmd *cmd, t_data *data, int qm_o, int qm_d)
{
	int	i;

	i = 0;
	cmd->count_redir = 0;
	while (cmd->str[i] != '\0')
	{
		ms_switch_qm(cmd->str[i], &qm_o, &qm_d);
		if ((cmd->str[i] == '>' || cmd->str[i] == '<')
			&& qm_d == 1 && qm_o == 1)
		{
			if ((cmd->str[i] == '>' && cmd->str[i + 1] == '>')
				|| (cmd->str[i + 1] == '<' && cmd->str[i] == '<')
				|| (cmd->str[i] == '<' && cmd->str[i + 1] == '>'))
				i++;
			i++;
			while (cmd->str[i] == ' ' && cmd->str[i] != '\0')
				i++;
			if (ms_error_parse_redir(data, cmd->str, i) == -1)
				return (-1);
			cmd->count_redir++;
		}
		else
			i++;
	}
	return (0);
}

int	ms_cycle_of_record_redir(t_cmd *cmd, t_data *data, int qm_o, int qm_d)
{
	int	i;
	int	num_redir;

	i = 0;
	num_redir = 0;
	while (cmd->str[i] != '\0')
	{
		ms_switch_qm(cmd->str[i], &qm_o, &qm_d);
		if ((cmd->str[i] == '>' || cmd->str[i] == '<')
			&& qm_d == 1 && qm_o == 1)
		{
			if (ms_record_redir_and_file(cmd, i, num_redir, data) == -1)
				return (-1);
			ms_replase_key_to_value(&cmd->str, data->tmp.size_cut, NULL, i);
			num_redir++;
		}
		i++;
	}
	if (cmd->str[0] == '\0' || cmd->str[0] == ' ')
	{
		i = 0;
		while(cmd->str[i] == ' ')
			i++;
		if (cmd->str[i] == '\0')
			ms_free_str(&cmd->str);
	}
	return (0);
}

int	ms_found_redirect(t_cmd *cmd, t_data *data)
{
	int	qm_d;
	int	qm_o;

	qm_o = 1;
	qm_d = 1;
	if (ms_count_redirect(cmd, data, qm_o, qm_d) == -1)
		return (-1);
	ms_malloc_arr_int(&cmd->redir, cmd->count_redir); // free +
	ms_malloc_array(&cmd->file, cmd->count_redir); // free +
	ms_cycle_of_record_redir(cmd, data, qm_o, qm_d);
	return (0);
}
