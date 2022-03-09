/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:58:28 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/09 19:06:41 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	rewrite_dir(t_data *data)
{
	char	*tmp_str;

	tmp_str = NULL;
	ms_free_str(&data->prev_dir);
	data->prev_dir = ft_strdup(data->cur_dir);
	ms_free_str(&data->cur_dir);
	tmp_str = getcwd(NULL, 0);
	data->cur_dir = ft_strdup(tmp_str);
	ms_free_str(&tmp_str);
	check_pwd_and_rewrite(data);
	ms_check_oldpwd_rewrite(data);
}

static void	minus(char *arg_way, t_data *data, int i)
{
	if (arg_way[i + 1] == '\0')
	{
		if (data->prev_dir == NULL || data->flag_old == 0)
			ms_print_error_builtin(NULL, 1);
		else
		{
			chdir(data->prev_dir);
			data->flag_old = 1;
			rewrite_dir(data);
			printf ("%s\n", data->cur_dir);
		}
	}
	else
	{
		data->num_error = 1;
		ms_print_error_builtin(&arg_way[i + 1], 2);
	}
}

static void	tilda_slesh_dir(char *arg_way, t_data *data, int i)
{
	char	*tail_str;
	char	*new_str;

	tail_str = NULL;
	new_str = NULL;
	ms_malloc_str(&tail_str, ft_strlen(arg_way));
	while (arg_way[i] != '\0')
	{
		tail_str[i] = arg_way[i + 1];
		i++;
	}
	tail_str[i] = '\0';
	new_str = ft_strjoin(data->home_dir, tail_str);
	ms_free_str(&tail_str);
	if (chdir(new_str) == -1)
	{
		data->num_error = 1;
		ms_print_error_builtin(new_str, 3);
	}
	else
	{
		data->flag_old = 1;
		rewrite_dir(data);
	}
	free (new_str);
}

static void	tilda(t_data *data)
{
	chdir(data->home_dir);
	data->flag_old = 1;
	rewrite_dir(data);
}

void	ms_cd(char *arg_way, t_data *data, int i)
{
	if ((!arg_way) || (arg_way[i] == '~' && arg_way[i + 1] == '\0'))
		tilda(data);
	else if (arg_way[i] == '~' && arg_way[i + 1] == '/')
	{
		if (arg_way[i + 2] == '\0')
			tilda(data);
		else
			tilda_slesh_dir(arg_way, data, 0);
	}
	else if (arg_way[i] == '-')
		minus(arg_way, data, 0);
	else
	{
		if (chdir(arg_way) == -1)
		{
			data->num_error = 1;
			ms_print_error_builtin(arg_way, 3);
		}
		else
		{
			data->flag_old = 1;
			rewrite_dir(data);
		}
	}
}
