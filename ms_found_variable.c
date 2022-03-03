#include "minishell.h"

void	ms_add_tmp_variable(t_data *data, char *var)
{
	int i;

	i = 0;
	char **tmp;
	data->num_tmp_var++;
	if (data->num_tmp_var == 1)
	{
		ms_malloc_array(&data->tmp_var, data->num_tmp_var);
		data->tmp_var[i] = ft_strdup(var);
		data->tmp_var[i + 1] = NULL;
	}
	else if (data->num_tmp_var > 1)
	{
		tmp = data->tmp_var;
		ms_malloc_array(&data->tmp_var, data->num_tmp_var);
		while (tmp[i] != NULL)
		{
			data->tmp_var[i] = ft_strdup(tmp[i]);
			i++;
		}
		data->tmp_var[i] = ft_strdup(var);
		data->tmp_var[i + 1] = NULL;
		if (tmp)
			ms_free_arr(&tmp);
	}
	i = 0; //// распечатка убрать
	while (i < data->num_tmp_var)
	{
		printf("tmp_var = %s\n", data->tmp_var[i]);
		i++;
	}
}

int	ms_cut_array_arg(char ***arr, int *count_arr, int y)
{
	int i;
	char **arr_tmp;

	i = 0;
	arr_tmp = (*arr);
	(*count_arr)--;
	if ((*count_arr) == 0)
	{
		ms_free_arr(arr);
		return (YES);
	}
	ms_malloc_array(arr, (*count_arr));
	while (i < y)
	{
		(*arr)[i] = ft_strdup(arr_tmp[i]);
		i++;
	}
	while (i < (*count_arr))
	{
		(*arr)[i] = ft_strdup(arr_tmp[i + 1]);
		i++;
	}
	(*arr)[i] = NULL;
	ms_free_arr(&arr_tmp);
	return (NO);
}

void	ms_found_variable(t_data *data)
{
	int i;

	i = 0;
	while (i < data->cmd[0].num_array_arg)
	{
		if (ms_valid_export(data->cmd[0].array_arg[0]) != ADD_TO_OLD
			&& ms_valid_export(data->cmd[0].array_arg[0]) != ADD_NEW)
			return ;
		i++;
	}
	while (data->cmd[0].num_array_arg != 0 && data->empty_str == NO)
	{
		if (ms_valid_export(data->cmd[0].array_arg[0]) != ERR_EXPORT)
		{
			ms_add_tmp_variable(data, data->cmd[0].array_arg[0]);
			data->empty_str = ms_cut_array_arg(&data->cmd[0].array_arg,
				&data->cmd[0].num_array_arg, 0);
		}
		else
			return ;
	}
}