/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:09:42 by obeedril          #+#    #+#             */
/*   Updated: 2022/03/11 21:09:44 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free_str(char **tmp_str);
void	ms_free_arr(char ***arr);
void	ms_free_int_arr(int **int_arr);

void	ms_free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	ms_free_arr(char ***arr)
{
	int	i;

	i = 0;
	if (**arr)
	{
		while ((*arr)[i] != NULL)
		{
			free((*arr)[i]);
			(*arr)[i] = NULL;
			i++;
		}
		if ((*arr)[i])
		{
			free((*arr)[i]);
			(*arr)[i] = NULL;
		}
		free(*arr);
		*arr = NULL;
	}
}

void	ms_free_int_arr(int **int_arr)
{
	int	i;

	i = 0;
	if (*int_arr)
	{
		free(*int_arr);
		*int_arr = NULL;
	}
}
