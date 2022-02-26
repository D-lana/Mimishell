#include "minishell.h"

int ms_error_parse_redir(t_data *data, char *s, int i)
{
	if (s[i] == '>' || s[i] == '<' || s[i] == '\0')
	{
		data->num_error = ERR_TOKEN;
		if (s[i] == '\0')
			ms_error(&data->num_error, "newline");
		if (s[i] == '>')
		{
			if (s[i + 1] == '>')
				ms_error(&data->num_error, ">>");
			else
				ms_error(&data->num_error, ">");
		}
		if (s[i] == '<')
		{
			if (s[i + 1] == '<')
				ms_error(&data->num_error, "<<");
			else if (s[i + 1] == '>')
				ms_error(&data->num_error, "<>");
			else 
				ms_error(&data->num_error, "<");
		}
		return (-1);
	}
	return (0);
}

void	ms_init_emum_redir(t_cmd *cmd, int *i_orig, int num_redir)
{
	int i;

	i = (*i_orig);
	if (cmd->str[i] == '>')
		cmd->redir[num_redir] = REDIR_W; // >;
	else if (cmd->str[i] == '<')
		cmd->redir[num_redir] = REDIR_R; // <;
	if (cmd->str[i] == '>' && cmd->str[i + 1] == '>')
	{
		cmd->redir[num_redir] = REDIR_W_ADD; // >>
		i++;
	}
	else if (cmd->str[i] == '<' && cmd->str[i + 1] == '<')
	{
		cmd->redir[num_redir] = HEREDOC; // <<
		i++;
	}
	else if (cmd->str[i] == '<' && cmd->str[i + 1] == '>')
	{
		cmd->redir[num_redir] = REDIR_ROMB; // <>
		i++;
	}
	i++;
	(*i_orig) = i;
}

void	ms_record_redir_and_file(t_cmd *cmd, int i, int num_redir, t_data *d)
{
	int start;
	int qm_o = 1;
	int qm_d = 1;

	start = 0;
	d->tmp.size_str = 0;
	d->tmp.size_cut = i;
	ms_init_emum_redir(cmd, &i, num_redir);
	while (cmd->str[i] == ' ' && cmd->str[i] != '\0')
		i++;
	start = i;
	while(cmd->str[i] != '\0')
	{
		ms_switch_qm(cmd->str, i, &qm_o, &qm_d);
		if (cmd->str[i] == ' ' && qm_o == 1 && qm_d == 1)
			break;
		d->tmp.size_str++;
		i++;
	}
	if (qm_o != 1 || qm_d != 1)
		write(1, "Oppps!\n", 8); ///////////// ошибка в названии файла - незакрытая кавычка
	ms_malloc_str(&cmd->file[num_redir], d->tmp.size_str);
	ms_record_str(&cmd->file[num_redir], cmd->str, start, d->tmp.size_str);
	d->tmp.size_cut = i - d->tmp.size_cut;
}

int	ms_count_redirect(t_cmd *cmd, t_data *data)
{
	int	i;
	int	qm_d;
	int	qm_o;

	qm_o = 1;
	qm_d = 1;
	i = 0;
	data->count_redir = 0;
	while (cmd->str[i] != '\0')
	{
		ms_switch_qm(cmd->str, i, &qm_o, &qm_d);
		if ((cmd->str[i] == '>' || cmd->str[i] == '<') && qm_d == 1 && qm_o == 1)
		{
			if ((cmd->str[i] == '>' && cmd->str[i + 1] == '>') 
				|| (cmd->str[i + 1] == '<' && cmd->str[i] == '<'))
				i++;
			i++;
			while (cmd->str[i] == ' ' && cmd->str[i] != '\0')
				i++;
			if (ms_error_parse_redir(data, cmd->str, i) == -1)
				return (-1);
			data->count_redir++;
		}
		else
			i++;
	}
	return (0);
}

int ms_found_redirect(t_cmd *cmd, t_data *data)
{
	int			i;
	int			num_redir;
	int qm_d;
	int qm_o;

	qm_o = 1;
	qm_d = 1;
	i = 0;
	num_redir = 0;
	if (ms_count_redirect(cmd, data) == -1)
		return (-1);
	cmd->redir = (int *)malloc(sizeof(int) * (data->count_redir + 1));
	ms_malloc_array(&cmd->file, data->count_redir);
	while (cmd->str[i] != '\0')
	{
		ms_switch_qm(cmd->str, i, &qm_o, &qm_d);
		if ((cmd->str[i] == '>' || cmd->str[i] == '<') && qm_d == 1 && qm_o == 1)
		{
			ms_record_redir_and_file(cmd, i, num_redir, data);
			ms_replase_key_to_value(&cmd->str, data->tmp.size_cut, NULL, i);
			num_redir++;
		}
		i++;
	}
	if (cmd->str[0] == '\0')
	{
		ms_free_str(&cmd->str);
		//printf("cmd->str %s\n", cmd->str);
		//cmd->str = NULL;
	}
	return (0);
}
