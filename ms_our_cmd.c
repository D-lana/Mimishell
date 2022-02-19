#include "minishell.h"

int		ms_our_cmd(t_data *data, char **env);
void	ms_echo(t_data *data, int i);
void	ms_env(t_data *data, char **env);
void	ms_export(t_data *data, char **env);
void	ms_unset(t_data *data, char **env);

int	ms_our_cmd(t_data *data, char **env)
{
	int i;

	i = 0;
	if (data->num_error != 0 || data->empty_str == YES)
		return(-1);
	if(ft_strncmp(data->cmd[i].array_arg[0], "pwd\0", 3) == 0)
		ms_pwd(); // obeedril changes
	else if(ft_strncmp(data->cmd[i].array_arg[0], "cd\0", 3) == 0)
		ms_cd(data->cmd[i].array_arg[1], data, 0);
	else if(ft_strncmp(data->cmd[i].arg[0].str, "echo\0", 5) == 0)
		ms_echo(data, 0);
	else if(ft_strncmp(data->cmd[i].array_arg[0], "exit\0", 5) == 0)
		ms_exit(data, data->cmd[i].num_array_arg, data->cmd[i].array_arg[1]); // obeedril 
	else if(ft_strncmp(data->cmd[i].array_arg[0], "env\0", 4) == 0)
		ms_env(data, env);
	else if(ft_strncmp(data->cmd[i].arg[0].str, "export\0", 7) == 0)
		write(1, "its export!\n", 13);// ms_export(data, env);
	else if(ft_strncmp(data->cmd[i].arg[0].str, "unset\0", 6) == 0)
		write(1, "its unset!\n", 12);
	else
		write(1, "its not my cmd!\n", 17);	
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

void	ms_env(t_data *data, char **env)
{
	int y;
	int	x;
	
	y = 0;
	x = 0;
	while (env[y] != 0)
		y++;
	ms_malloc_array(&data->our_env, y);
	y = 0;
	while (env[y] != 0)
	{
		while (env[y][x] != '\0')
		{
			x++;
		}
		ms_malloc_str(&data->our_env[y], x);
		ms_record_str(&data->our_env[y], env[y], 0, x);
		printf("%s\n", data->our_env[y]);
		y++;
		x = 0;
	}
}

// void	ms_export(t_data *data, char **env)
// {
// 	int i;
// 	i = 0;
// 	//t_data *new = data;
// 	//const char *env;
// 	//env = getenv("All");
// 	while (env[i] != 0)
// 	{
// 		printf("%s\n", env[i]);
// 		i++;
// 	}
// }
