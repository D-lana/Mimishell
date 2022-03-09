/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_errors_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:25:30 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/09 19:47:36 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_print_errors_chfa(char *str, int flag)
{
	if (flag == 1 || flag == ERR_CMD)
	{
		ft_putstr_fd("MiMishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (flag == 2)
	{
		ft_putstr_fd("MiMishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	if (flag == 3)
	{
		ft_putstr_fd("MiMishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	if (flag == 4)
	{
		ft_putstr_fd("MiMishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (-1);
}

void	ms_print_error_builtin(char *str, int flag)
{
	if (flag == 1)
		ft_putstr_fd("Mimishell: cd: OLDPWD not set\n", 2);
	if (flag == 2)
	{
		ft_putstr_fd("Mimishell: cd: -", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("cd: usage: cd [-L|-P] [dir]\n", 2);
	}
	if (flag == 3)
	{
		ft_putstr_fd("Mimishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	if (flag == 4)
	{
		ft_putstr_fd("\bexit\n", 2);
		ft_putstr_fd("Mimishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	if (flag == 5)
		ft_putstr_fd("\bexit\nMimishell: exit: too many arguments\n", 2);
}
