/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:29:59 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/14 15:58:16 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd(data->cur_dir, 1);
		write (1, "\n", 1);
	}
	else
	{
		ft_putstr_fd(cwd, 1);
		write (1, "\n", 1);
		ms_free_str(&cwd);
	}
}
