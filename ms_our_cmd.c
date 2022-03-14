/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_our_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:45:38 by dlana             #+#    #+#             */
/*   Updated: 2022/03/13 10:25:17 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_build_in_or_no(t_data *data, int i)
{
	if (ft_strncmp(data->cmd[i].array_arg[0], "pwd\0", 4) == 0)
		data->build_in = YES;
	else if (ft_strncmp(data->cmd[i].array_arg[0], "cd\0", 3) == 0)
		data->build_in = YES;
	else if (ft_strncmp(data->cmd[i].array_arg[0], "echo\0", 5) == 0)
		data->build_in = YES;
	else if (ft_strncmp(data->cmd[i].array_arg[0], "exit\0", 5) == 0)
		data->build_in = YES;
	else if (ft_strncmp(data->cmd[i].array_arg[0], "env\0", 4) == 0)
		data->build_in = YES;
	else if (ft_strncmp(data->cmd[i].array_arg[0], "export\0", 7) == 0)
		data->build_in = YES;
	else if (ft_strncmp(data->cmd[i].array_arg[0], "unset\0", 6) == 0)
		data->build_in = YES;
	else
		data->build_in = NO;
}

int	ms_build_in_cmd(t_data *data, int i, char **line)
{
	if (ft_strncmp(data->cmd[i].array_arg[0], "pwd\0", 4) == 0)
		ms_pwd(data);
	else if (ft_strncmp(data->cmd[i].array_arg[0], "cd\0", 3) == 0)
		ms_cd(data->cmd[i].array_arg[1], data, 0);
	else if (ft_strncmp(data->cmd[i].array_arg[0], "echo\0", 5) == 0)
		ms_echo(data, i);
	else if (ft_strncmp(data->cmd[i].array_arg[0], "exit\0", 5) == 0)
		ms_exit(data, data->cmd[i].num_array_arg,
			data->cmd[i].array_arg[1], line);
	else if (ft_strncmp(data->cmd[i].array_arg[0], "env\0", 4) == 0)
		ms_env(data);
	else if (ft_strncmp(data->cmd[i].array_arg[0], "export\0", 7) == 0)
		ms_export(data, i);
	else if (ft_strncmp(data->cmd[i].array_arg[0], "unset\0", 6) == 0)
		ms_unset(data, i);
	else
	{
		data->build_in = NO;
		return (1);
	}
	return (0);
}

int	ms_our_cmd(t_data *data, int i, char **line)
{
	pid_t	pid;

	if (data->num_error != 0 || data->cmd[i].array_arg == NULL)
		return (-1);
	ms_build_in_or_no(data, i);
	if (i == 0 && data->build_in == YES)
		ms_build_in_cmd(data, i, line);
	else if (data->build_in == YES)
	{
		pid = fork();
		if (pid == -1)
			perror("fork error");
		else if (pid == 0)
			exit(ms_build_in_cmd(data, i, line));
	}
	else
		ms_execve(data->cmd, data, i);
	unlink("tmp");
	return (0);
}
