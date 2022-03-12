/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:09:54 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/11 21:09:56 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_malloc_array(char ***array, int size)
{
	(*array) = (char **)malloc(sizeof(char *) * (size + 1));
	if ((*array) == NULL)
	{
		write(2, "Mimisell: Allocation memory error\n", 35);
		exit(EXIT_FAILURE);
	}
}

void	ms_malloc_str(char **name, int size)
{
	(*name) = malloc(sizeof(char) * (size + 1));
	if ((*name) == NULL)
	{
		write(2, "Mimisell: Allocation memory error\n", 35);
		exit(EXIT_FAILURE);
	}
}

void	ms_malloc_arg(t_arg **arg, int size)
{
	(*arg) = malloc(sizeof(t_arg) * (size + 1));
	if ((*arg) == NULL)
	{
		write(2, "Mimisell: Allocation memory error\n", 35);
		exit(EXIT_FAILURE);
	}
}

void	ms_malloc_cmd(t_cmd **cmd, int size)
{
	(*cmd) = malloc(sizeof(t_cmd) * (size + 1));
	if ((*cmd) == NULL)
	{
		write(2, "Mimisell: Allocation memory error\n", 35);
		exit(EXIT_FAILURE);
	}
}

void	ms_malloc_arr_int(int **arr_int, int size)
{
	(*arr_int) = (int *)malloc(sizeof(int) * (size + 1));
	if ((*arr_int) == NULL)
	{
		write(2, "Mimisell: Allocation memory error\n", 35);
		exit(EXIT_FAILURE);
	}
}
