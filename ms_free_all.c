#include "minishell.h"

void	ms_free_all(t_data *data, char **line)
{
	//ms_free_arr(&data->our_env);
	ms_free_cycle(data, line);
	//ms_free_arr(&data->tmp_var);
	ms_free_str(&data->prev_dir);
	ms_free_str(&data->cur_dir);

}

void	ms_free_cycle(t_data *data, char **line)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	ms_free_str(line);
	if (data->num_cmd > 0)
	{
		while (y < data->num_cmd)
		{
			ms_free_str(&data->cmd[y].str); // fsanitize=address при выходе из мимишелл
			if (data->cmd[y].num_arg > 0)
			{
				while (x < data->cmd[y].num_arg)
				{
					ms_free_str(&data->cmd[y].arg[x].str);
					x++;
				}
				free(data->cmd[y].arg);
				//printf("free data->cmd.arg!\n");
				data->cmd[y].arg = NULL;
			}
			if (data->cmd[y].array_empty == NO)
				ms_free_arr(&data->cmd[y].array_arg);
			if (data->cmd[y].count_redir > 0)
			{
				ms_free_int_arr(&data->cmd[y].redir);
				ms_free_arr(&data->cmd[y].file);
			}
			y++;
		}
		free(data->cmd);
		//printf("free data->cmd!\n");
		data->cmd = NULL;
	}
}
