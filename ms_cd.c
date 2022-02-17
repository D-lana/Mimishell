/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:58:28 by obeedril          #+#    #+#             */
/*   Updated: 2022/02/17 14:43:46 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	rewrite_dir(t_data *data)
{
	char	cwd[256];

	data->prev_dir = ft_strdup(data->cur_dir);
	data->cur_dir = getcwd(cwd, sizeof(cwd));
}

static void	minus(char *arg_way, t_data *data, int i)
{
	char	cwd[256];

	if (arg_way[i + 1] == '\0')
	{
		if (data->prev_dir == NULL)
			printf("Mimishell: cd: OLDPWD not set\n");
		else
		{
			data->cur_dir = getcwd(cwd, sizeof(cwd));
			chdir(data->prev_dir);
			rewrite_dir(data);
		}
	}
	else
	{
		data->num_error = 1;
		printf("Mimishell: cd: -%c: invalid option\n", arg_way[i + 1]);
		printf("cd: usage: cd [-L|-P] [dir]\n");
	}
}

static void	tilda_slesh_dir(char *arg_way, t_data *data, int i)
{
	char	*tail_str;
	char	*new_str;
	char	cwd[256];

	tail_str = NULL;
	new_str = NULL;
	ms_malloc_str(&tail_str, ft_strlen(arg_way));
	while (arg_way[i] != '\0')
	{
		tail_str[i] = arg_way[i + 1];
		i++;
	}
	tail_str[i] = '\0';
	i = 0;
	new_str = ft_strjoin(data->home_dir, tail_str);
	free (tail_str);
	data->cur_dir = getcwd(cwd, sizeof(cwd));
	if (chdir(new_str) == -1)
	{
		data->num_error = 1;
		printf ("Mimishel: cd: %s: No such file or directory\n", arg_way);
	}
	else
		rewrite_dir(data);
	free (new_str);
}

static void	tilda(t_data *data)
{
	char	cwd[256];

	data->cur_dir = getcwd(cwd, sizeof(cwd));
	chdir(data->home_dir);
	rewrite_dir(data);
}

void	ms_cd(char *arg_way, t_data *data, int i)
{
	char	cwd[256];

	if ((!arg_way) || (arg_way[i] == '~' && arg_way[i + 1] == '\0'))
		tilda(data);
	else if (arg_way[i] == '~' && arg_way[i + 1] == '/')
	{
		if (arg_way[i + 2] == '\0')
			tilda(data);
		else
			tilda_slesh_dir(arg_way, data, 0);
	}
	else if (arg_way[i] == '-') // && arg_way[i + 1] == '\0')
		minus(arg_way, data, 0);
	else
	{
		data->cur_dir = getcwd(cwd, sizeof(cwd));
		if (chdir(arg_way) == -1)
		{
			data->num_error = 1;
			printf("Mimishell: cd: %s: No such file or directory\n", arg_way);
		}
		else
			rewrite_dir(data);
	}
}
