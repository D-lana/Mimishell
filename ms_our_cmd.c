#include "minishell.h"

int		ms_our_cmd(t_data *data, char **env);
void	ms_echo(t_data *data, int i);
void	ms_env(char **env);
void	ms_export(t_data *data, char **env);
void	ms_unset(t_data *data, char **env);

int	ms_our_cmd(t_data *data, char **env)
{
	int i;

	i = 0;
	if (data->num_error != 0)
		return(-1);
	if(ft_strncmp(data->cmd[i].array_arg[0], "pwd\0", 3) == 0)
		ms_pwd(); // obeedril changes
	else if(ft_strncmp(data->cmd[i].array_arg[0], "cd\0", 3) == 0)
		ms_cd(data->cmd[i].array_arg[1], data, 0); //obeedril changes // исправить на array_arg[1]
	else if(ft_strncmp(data->cmd[i].arg[0].str, "echo\0", 5) == 0)
		ms_echo(data, 0);
	else if(ft_strncmp(data->cmd[i].array_arg[0], "exit\0", 5) == 0)
		ms_exit(data, data->cmd[i].array_arg[1], 0); // obeedril 
		//write(1, "its exit!\n", 11);
	else if(ft_strncmp(data->cmd[i].arg[0].str, "env\0", 4) == 0)
		ms_env(env);	
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
	while (j < data->cmd[i].num_arg) ////////////// распечатка, убрать)
	{		
		if (j == 1 && ft_strncmp(data->cmd[i].arg[j].str, "-n\0", 3) == 0)
		{
			n = YES;
			j++;
		}
		printf("%s", data->cmd[i].arg[j].str);
		if(data->cmd[i].arg[j].space == YES)
			printf(" ");
		j++;
	}
	j = 1;
	if (n == YES)
		printf("\b");
	else
		printf("\n");
}

void	ms_env(char **env)
{
	int i;
	i = 0;
	//t_data *new = data;
	//const char *env;
	//env = getenv("All");
	while (env[i] != 0)
	{
		printf("%s\n", env[i]);
		i++;
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
