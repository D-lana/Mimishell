#include "minishell.h"

void	ms_init_emum_redir(t_cmd *cmd, int *i_orig, int num_redir)
{
	int	i;

	i = (*i_orig);
	if (cmd->str[i] == '>')
		cmd->redir[num_redir] = REDIR_W;
	else if (cmd->str[i] == '<')
		cmd->redir[num_redir] = REDIR_R;
	if (cmd->str[i] == '>' && cmd->str[i + 1] == '>')
	{
		cmd->redir[num_redir] = REDIR_W_ADD;
		i++;
	}
	else if (cmd->str[i] == '<' && cmd->str[i + 1] == '<')
	{
		cmd->redir[num_redir] = HEREDOC;
		i++;
	}
	else if (cmd->str[i] == '<' && cmd->str[i + 1] == '>')
	{
		cmd->redir[num_redir] = REDIR_ROMB;
		i++;
	}
	i++;
	(*i_orig) = i;
}

int	ms_err_name_file(t_data *data, int qm_o, int qm_d)
{
	char	qmd[2];

	qmd[0] = DOUBLE_Q_MARK;
	qmd[1] = '\0';
	data->num_error = ERR_TOKEN;
	if (qm_o != 1)
		ms_error(ERR_TOKEN, "'");
	else if (qm_d != 1)
		ms_error(ERR_TOKEN, qmd);
	return (-1);
}

int	ms_cut_qm_in_name_file(char **file)
{
	int		i;
	char	qm;

	i = 0;
	qm = 0;
	while ((*file)[i] != '\0')
	{
		qm = (*file)[i];
		if (qm == 34 || qm == 39)
		{
			ms_replase_key_to_value(file, 1, NULL, i);
			while ((*file)[i] != qm && (*file)[i] != '\0')
				i++;
			if ((*file)[i] != '\0')
				ms_replase_key_to_value(file, 1, NULL, i);
		}
		else
			i++;
	}
	return (0);
}

void	ms_found_dollar_in_name_file(t_data *data, char **file)
{
	int		i;
	char	qm;

	i = 0;
	qm = 0;
	while ((*file)[i] != '\0')
	{
		if ((*file)[i] == ONE_Q_MARK && qm != ONE_Q_MARK)
			qm = ONE_Q_MARK;
		else if ((*file)[i] == ONE_Q_MARK && qm == ONE_Q_MARK)
			qm = 0;
		if (qm != ONE_Q_MARK)
		{
			data->name_file = YES;
			ms_found_dollar(data, file, qm, &i);
			data->name_file = NO;
		}
		else
			i++;
	}
}

int	ms_measure_size_file_name(t_data *d, char *str, int *i)
{
	int	qm_o;
	int	qm_d;
	int	size_str;

	size_str = 0;
	qm_o = 1;
	qm_d = 1;
	while (str[(*i)] != '\0')
	{
		ms_switch_qm(str[(*i)], &qm_o, &qm_d);
		if (str[(*i)] == ' ' && qm_o == 1 && qm_d == 1)
			break ;
		size_str++;
		(*i)++;
	}
	if (qm_o != 1 || qm_d != 1)
		return (ms_err_name_file(d, qm_o, qm_d));
	return (size_str);
}

int	ms_record_redir_and_file(t_cmd *cmd, int i, int num_redir, t_data *d)
{
	int	start;
	int	size_str;

	start = 0;
	d->tmp.size_cut = i;
	ms_init_emum_redir(cmd, &i, num_redir);
	while (cmd->str[i] == ' ' && cmd->str[i] != '\0')
		i++;
	start = i;
	size_str = ms_measure_size_file_name(d, cmd->str, &i);
	if (size_str == -1)
		return (-1);
	ms_malloc_str(&cmd->file[num_redir], size_str);
	ms_record_str(&cmd->file[num_redir], cmd->str, start, size_str);
	ms_found_dollar_in_name_file(d, &cmd->file[num_redir]);
	ms_cut_qm_in_name_file(&cmd->file[num_redir]);
	d->tmp.size_cut = i - d->tmp.size_cut;
	return (0);
}
