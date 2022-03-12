/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_errors_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:22:14 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/12 14:27:42 by obeedril         ###   ########.fr       */
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
		ft_putstr_fd(": permission denied\n", 2);
	}
	if (flag == 4)
	{
		ft_putstr_fd("MiMishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
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
		ft_putstr_fd(": no such file or directory\n", 2);
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

int	ms_error(int error, char *str)
{
	if (error == ERR_TOKEN && (str[0] == 34 || str[0] == 39))
	{
		ft_putstr_fd("Mimishell: unexpected EOF while ", 2);
		ft_putstr_fd("looking for matching '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (error == ERR_TOKEN)
	{
		ft_putstr_fd("Mimishell: syntax error near unexpected token '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (error == ERR_Q_MARK)
		write(2, "Mimisell: skipped quotation_marks\n", 35);
	else if (error == ERR_NUM_ONE && str[0] == '!')
	{
		ft_putstr_fd("Mimishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": event not found\n", 2);
	}
	return (-1);
}

int	ms_error_2(int error, int qm)
{
	char	a;

	a = qm;
	if (error == ERR_TOKEN && qm == 34)
	{
		ft_putstr_fd("Mimishell: unexpected EOF while ", 2);
		ft_putstr_fd("looking for matching '", 2);
		write(2, &a, 1);
		ft_putstr_fd("'\n", 2);
	}
	if (error == ERR_TOKEN && qm == 39)
	{
		ft_putstr_fd("Mimishell: unexpected EOF while ", 2);
		ft_putstr_fd("looking for matching '", 2);
		write(2, &a, 1);
		ft_putstr_fd("'\n", 2);
	}
	return (-1);
}

int	ms_err_export(int error, char *str)
{
	if (error == ERR_NUM_ONE)
	{
		ft_putstr_fd("Mimishell: export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	return (-1);
}

void	ms_err_argc_argv(int argc, char **argv, char **env)
{
	if (argc != 1 || argv == NULL || env == NULL)
	{
		ft_putstr_fd("Mimishell: this programm complies without arguments\n", 2);
		exit(127);
	}
}
