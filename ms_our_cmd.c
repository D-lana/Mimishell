#include "minishell.h"

int		ms_our_cmd(t_data *data);
void	ms_echo(t_data *data, int i);
void	ms_env(t_data *data);
void	ms_export(t_data *data);
void	ms_unset(t_data *data, int i);

int	ms_our_cmd(t_data *data)
{
	int i;

	i = 0;
	if (data->num_error != 0 || data->empty_str == YES)
		return(-1);
	if(ft_strncmp(data->cmd[i].array_arg[0], "pwd\0", 3) == 0)
		ms_pwd(); // obeedril changes
	else if(ft_strncmp(data->cmd[i].array_arg[0], "cd\0", 3) == 0)
		ms_cd(data->cmd[i].array_arg[1], data, 0);
	else if(ft_strncmp(data->cmd[i].array_arg[0], "echo\0", 5) == 0)
		ms_echo(data, 0);
	else if(ft_strncmp(data->cmd[i].array_arg[0], "exit\0", 5) == 0)
		ms_exit(data, data->cmd[i].num_array_arg, data->cmd[i].array_arg[1]); // obeedril 
	else if(ft_strncmp(data->cmd[i].array_arg[0], "env\0", 4) == 0)
		ms_env(data);
	else if(ft_strncmp(data->cmd[i].array_arg[0], "export\0", 7) == 0)
		ms_export(data);
	else if(ft_strncmp(data->cmd[i].array_arg[0], "unset\0", 6) == 0)
	{
		if (data->cmd[i].array_arg[1] != NULL)
			ms_unset(data, i);
		else
			return(0);
	}
	else
		ms_execve(data->cmd, data);
	return(0);
}

void	ms_echo(t_data *data, int i)
{
	int j;
	int n;

	j = 1;
	n = NO;
	while (j < data->cmd[i].num_array_arg)
	{		
		if (j == 1 && ft_strncmp(data->cmd[i].array_arg[j], "-n\0", 3) == 0)
		{
			n = YES;
			j++;
		}
		if (data->cmd[i].array_arg[j] != NULL)
			printf("%s ", data->cmd[i].array_arg[j]);
		j++;
	}
	if (n != YES)
		printf("\n");
	else
		printf("\b");
}

void	ms_env(t_data *data)
{
	int	y;

	y = 0;
	while (y < data->num_env)
	{
		printf("%s\n", data->our_env[y]);
		//printf("%s=", data->env->key);
		//printf("%s\n", data->env->value);
		//data->env = data->env->next;
		y++;
	}
}
