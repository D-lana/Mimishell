#include "minishell.h"

int ms_record_one_str(char **str, char *line, int *start, int *num)
{
	int size;
	int i;
	int qm_d;
	int qm_o;

	size = 0;
	i = 0;
	qm_o = 1;
	qm_d = 1;
	while (line[(*start) + size] != '\0' && line[(*start) + size] != '|')
	{
		ms_switch_qm(line[(*start) + size], &qm_o, &qm_d);
		if (line[(*start) + size + 1] == '|' && (qm_o == -1 || qm_d == -1))
			size++;
		size++;
	}
	ms_malloc_str(str, size);
	//printf("alloc str data->cmd[num].str\n");
	while(i < size)
	{
		(*str)[i] = line[(*start) + i];
		i++;
	}
	(*str)[i] = '\0';
	(*num)++;
	if (line[(*start) + i] == '|') 
		i++;
	(*start) = (*start) + i;
	return(0);
}

int	ms_count_pipe(t_data *data, char *line, int qm_d, int qm_o)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		ms_switch_qm(line[i], &qm_o, &qm_d);
		if (line[i] == '|' &&  qm_o == 1 && qm_d == 1)
		{
			i++;
			if (line[i] == ' ')
			{
				while (line[i] == ' ')
					i++;
			}
			if (line[i] == '\0')
			{
				data->num_error = ERR_TOKEN;
				data->num_cmd = 0;
				return(ms_error(data->num_error, "|"));
			} 
			data->num_cmd++;
		}
		i++;
	}
	return (0);
}

int ms_count_and_record_cmd(t_data *data, char *line)
{
	int	i;
	int num;
	int qm_d;
	int qm_o;

	i = 0;
	qm_o = 1;
	qm_d = 1;
	data->num_cmd = 1;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return(data->empty_str = YES);
	if (line[i] == '|')
	{
		data->num_error = ERR_TOKEN;
		data->num_cmd = 0;
		return(ms_error(data->num_error, "|"));
	}
	if (ms_count_pipe(data, line, 1, 1) == -1)
		return (-1);
	ms_malloc_cmd(&data->cmd, data->num_cmd); /// free cmd +
	//printf("alloc massiv data->cmd\n");
	i = 0;
	while (data->num_cmd > i)
	{
		data->cmd[i] = (t_cmd){};
		i++;
	}
	i = 0;
	num = 0;
	while (line[i] != '\0')
		ms_record_one_str(&data->cmd[num].str, line, &i, &num);
	//i = 0;
	// while (i < data->num_cmd) ////////////// распечатка, убрать)
	// {
	// 	printf("%s", data->cmd[i].str);
	// 	printf("\n");
	// 	i++;
	// }
	return (0);
}