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
		if (line[(*start) + size] == DOUBLE_Q_MARK  && qm_o == 1)
			qm_d = qm_d * (-1);
		if (line[(*start) + size] == ONE_Q_MARK  && qm_d == 1)
			qm_o = qm_o * (-1);
		if (line[(*start) + size + 1] == '|' && (qm_o == -1 || qm_d == -1))
			size++;
		size++;
	}
	ms_malloc_str(str, size);
	while(i < size)
	{
		(*str)[i] = line[(*start) + i];
		i++;
	}
	(*str)[i] = '\0';
	(*num)++;
	//if (line[(*start) + i] == '|' && line[(*start) + i + 1] == '\0')
		//return(ms_error(ERR_PIPE)); //// возможно сюда нужно добавить предложение для ввода > и чтение с командной строки
	if (line[(*start) + i] == '|') 
		i++;
	(*start) = (*start) + i;
	return(0);
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
	if (line[i] == '|')
	{
		data->num_error = ERR_TOKEN;
		return(ms_error(&data->num_error, "|"));
	}
	while (line[i] != '\0')
	{
		if (line[i] == DOUBLE_Q_MARK && qm_o == 1)
			qm_d = qm_d * (-1);
		if (line[i] == ONE_Q_MARK && qm_d == 1)
			qm_o = qm_o * (-1);
		if (line[i] == '|' &&  qm_o == 1 && qm_d == 1)
		{
			//printf("qm = %d, %d", qm_d, qm_o);
			i++;
			if (line[i] == ' ')
			{
				while (line[i] == ' ')
					i++;
			}
			if (line[i] == '\0')
			{
				data->num_error = ERR_TOKEN;
				return(ms_error(&data->num_error, "|")); //// возможно сюда нужно добавить предложение для ввода > и чтение с командной строки
			} 
			data->num_cmd++;
		}
		i++;
	}
	ms_malloc_cmd(&data->cmd, data->num_cmd);
	i = 0;
	num = 0;
	while (line[i] != '\0')
	{
		ms_record_one_str(&data->cmd[num].str, line, &i, &num);
		//printf("line[i] = %c\n", line[i]);
	}
	//printf("data->num_cmd = %d\n", data->num_cmd);
	//i = 0;
	// while (i < data->num_cmd) ////////////// распечатка, убрать)
	// {
	// 	printf("%s", data->cmd[i].str);
	// 	printf("\n");
	// 	i++;
	// }
	return (0);
}