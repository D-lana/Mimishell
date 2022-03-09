#include "minishell.h"

void	ms_free_all(t_data *data, char **line)
{
	(void)line;
	ms_free_arr(&data->our_env);
	//ms_free_arr(&data->tmp_var); pointer being freed was not allocated
	//ms_free_cycle(data, line); pointer being freed was not allocated
	ms_free_str(&data->prev_dir);
	ms_free_str(&data->cur_dir);
}

void	ms_free_cycle(t_data *data, char **line)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	ms_free_str(line);
	while (y < data->num_cmd)
	{
		// while (i < data->cmd[y].num_arg)
		// {
		// 	ms_free_str(&data->cmd[y].arg[i].str);
		// 	//data->cmd[y].arg[i].str = NULL;
		// 	i++;
		// }
		// if (data->cmd[y].arg)
		// 	free(data->cmd[y].arg);
		// if (data->cmd[y].num_array_arg > 0)
		// 	ms_free_arr(&data->cmd[y].array_arg);
		// if (data->cmd->count_redir > 0)
		// {
		// 	ms_free_int_arr(&data->cmd[y].redir);
		// 	ms_free_arr(&data->cmd[y].file);
		// }
		y++;
	}
	if (data->cmd)
	{
		free(data->cmd);
		data->cmd = NULL;
	}
}
