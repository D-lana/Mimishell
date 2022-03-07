#include "minishell.h"

int		ms_our_cmd(t_data *data, int i);
void	ms_echo(t_data *data, int i);
void	ms_env(t_data *data);


void	ms_build_in_or_no(t_data *data, int i)
{
	
	if(ft_strncmp(data->cmd[i].array_arg[0], "pwd\0", 3) == 0)
		data->build_in = YES;
	else if(ft_strncmp(data->cmd[i].array_arg[0], "cd\0", 3) == 0)
		data->build_in = YES;
	else if(ft_strncmp(data->cmd[i].array_arg[0], "echo\0", 5) == 0)
		data->build_in = YES;
	else if(ft_strncmp(data->cmd[i].array_arg[0], "exit\0", 5) == 0)
		data->build_in = YES;
	else if(ft_strncmp(data->cmd[i].array_arg[0], "env\0", 4) == 0)
		data->build_in = YES;
	else if(ft_strncmp(data->cmd[i].array_arg[0], "export\0", 7) == 0)
		data->build_in = YES;
	else if(ft_strncmp(data->cmd[i].array_arg[0], "unset\0", 6) == 0)
		data->build_in = YES;
	else
		data->build_in = NO;
}


int	ms_build_in_cmd(t_data *data, int i)
{
	if(ft_strncmp(data->cmd[i].array_arg[0], "pwd\0", 3) == 0)
		ms_pwd(data); // obeedril changes
	else if(ft_strncmp(data->cmd[i].array_arg[0], "cd\0", 3) == 0)
		ms_cd(data->cmd[i].array_arg[1], data, 0);
	else if(ft_strncmp(data->cmd[i].array_arg[0], "echo\0", 5) == 0)
		ms_echo(data, i);
	else if(ft_strncmp(data->cmd[i].array_arg[0], "exit\0", 5) == 0)
		ms_exit(data, data->cmd[i].num_array_arg, data->cmd[i].array_arg[1]); // obeedril 
	else if(ft_strncmp(data->cmd[i].array_arg[0], "env\0", 4) == 0)
		ms_env(data);
	else if(ft_strncmp(data->cmd[i].array_arg[0], "export\0", 7) == 0)
		ms_export(data, i);
	else if(ft_strncmp(data->cmd[i].array_arg[0], "unset\0", 6) == 0)
		ms_unset(data, i);
	else
	{
		data->build_in = NO;
		return(1); //ms_execve(data->cmd, data, i);
	}
	return(0);
}

int	ms_our_cmd(t_data *data, int i)
{
	pid_t pid;

	if (data->num_error != 0 || data->empty_str == YES || data->cmd[i].array_arg == NULL)
		return(-1);
	ms_build_in_or_no(data, i);
	if (i == 0 && data->build_in == YES)
	{
		
			ms_build_in_cmd(data, i);
	}
	else if (data->build_in == YES)
	{
		if ((pid = fork()) == -1)
			perror("fork error");
		if (pid == 0)
		{
			ms_build_in_cmd(data, i);
			exit (0);
		}
			
	}
	else
	{
		//write(2,"jjjjjjjjj",10);
		ms_execve(data->cmd, data, i);
	}
	return(0);
}

int	ms_found_minus_n(char *arg)
{
	int i;

	i = 0;
	if (arg[i] == '\0')
		return (-1);
	if (arg[i] != '-' || arg[i + 1] != 'n')
		return (-1);
	i++;
	while (arg[i] == 'n' && arg[i] != '\0')
		i++;
	if (arg[i] != '\0')
		return (-1);
	return (0);
}

void	ms_echo(t_data *data, int i)
{
	int j;
	int n;

	j = 1;
	n = NO;
	while (j < data->cmd[i].num_array_arg)
	{		
		if (j == 1 && ms_found_minus_n(data->cmd[i].array_arg[j]) == 0) // ft_strncmp(data->cmd[i].array_arg[j], "-n\0", 3)
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
		if (ft_strncmp(data->our_env[y], "OLDPWD", 6) == 0)
		{
			if (data->prev_dir != NULL)
				printf("%s\n", data->our_env[y]);
		}
		else if (ft_strchr(data->our_env[y], 61) != NULL)
			printf("%s\n", data->our_env[y]);
		y++;
	}
}
