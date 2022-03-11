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

void ms_free_int_arr(int **int_arr)
{
	int	i;

	i = 0;
	if (*int_arr)
	{
		//printf("free num in_arr: %d\n", (*int_arr)[i]);
		free(*int_arr);
		*int_arr = NULL;
	}
}
