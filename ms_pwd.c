/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:29:59 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/08 12:34:29 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		printf("%s\n", data->cur_dir);
		//ft_putstr_fd(data->cur_dir, 2);
		//write (2, "\n", 1);
	}
	else
	{
		//ft_putstr_fd(cwd, 2);
		printf("%s\n", cwd);
		//write (2, "\n", 1);
	}
}
