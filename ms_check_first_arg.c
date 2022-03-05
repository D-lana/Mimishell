/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_first_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:48:49 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/05 20:37:50 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// bash-3.2$ ./libft
// bash: ./libft: is a directory
// bash-3.2$ echo $?

#include "minishell.h"

static int ms_check_way_itself(t_data *data, int find_cmd, int n)
{
	char	*str;
	char	*str_slesh;
	char	*str_way;
	
	str = NULL;
	str_way =NULL;
	str_slesh = NULL;
	str = getcwd(NULL, 0);
	str_slesh = ft_strjoin(str, "/");
	str_way = ft_strjoin(str_slesh, data->cmd[n].array_arg[0]);
	ms_free_str(&str_slesh);
	if (!access (str_way, 1))
	{
		write (1, "A\n", 2);
		find_cmd = -1; // нашла команду
		data->cmd[n].way_cmd = ft_strdup(str_way);
		//data->cmd[n].cur_way_cmd = ft_strdup(str_way); // отфришить где-нибудь в конце
	}
	else
	{
		write (1, "B\n", 2);
		find_cmd = -2;
		//printf("Mimishell: %s: Permission denied\n", data->cmd[n].array_arg[0]);
	}
	
	ms_free_str(&str_way);
	return (find_cmd);
}

static char	*add_slesh(char **arr_p, int i, int j)
{
	char	*str_slesh;
	str_slesh = NULL;
	ms_malloc_str(&str_slesh, ft_strlen(arr_p[i]) + 1);
	while (arr_p[i][j] != '\0')
	{
		str_slesh[j] = arr_p[i][j];
		j++;
	}
	str_slesh[j] = '/';
	str_slesh[j + 1] = '\0';
	return (str_slesh);
}

static int  check_str(t_data *data, char **arr_p, int i, int n)
{
	int		find_cmd;
	char	*str_slesh;
	char	*str_way;

	find_cmd = 0;
	str_way = NULL;
	//оттестить если первый аргумент редирект
	if ((data->cmd[n].array_arg[0][0] == '.' && data->cmd[n].array_arg[0][1] == '/'))
		find_cmd = ms_check_way_itself(data, find_cmd, n);
	else
	{
		while (arr_p[i])
		{
			str_slesh = add_slesh(arr_p, i, 0);
			str_way = ft_strjoin(str_slesh, data->cmd[n].array_arg[0]);
			ms_free_str(&str_slesh); // change
			if (!access (str_way, 1))
			{
				find_cmd = -1; // нашла команду
				data->cmd[n].way_cmd = ft_strdup(str_way); // отфришить где-нибудь в конце
				break ;
			}
			else
				find_cmd++;
			ms_free_str(&str_way); // changed free
			i++;
		}
	}
	return (find_cmd);
}

void	ms_check_first_arg(t_data *data)
{
	const char	*p;
	char		**arr_p;
	int			i;
	int			n;
	int			find_cmd;

	i = 0;
	n = 0;
	find_cmd = 0;
	if (data->num_error != 0 || data->empty_str == YES)
		return ;
	p = getenv("PATH");
	arr_p = ft_split(p, ':');
	while (n < data->num_cmd)
	{
		find_cmd = check_str(data, arr_p, i, n);
		if (find_cmd >= 0)
		{
			data->num_error = ERR_CMD;
			printf("Mimishell: %s: command not found\n",
				data->cmd[n].array_arg[0]);
			data->num_error = 127; // оставить?
		}
		if (find_cmd == -2)
		{
			printf("Mimishell: %s: Permission denied\n", data->cmd[n].array_arg[0]);
			data->num_error = 126;
					
		}
		n++;
	}
}
