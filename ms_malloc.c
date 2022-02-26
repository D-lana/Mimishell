#include "minishell.h"

void	ms_malloc_array(char ***array, int size);
void	ms_malloc_str(char **name, int size);
void	ms_malloc_arg(t_arg **arg, int size);
void	ms_malloc_cmd(t_cmd **cmd, int size);
int		*ms_malloc_arr_int(int **arr_int, int size);

void	ms_malloc_array(char ***array, int size) // ms_malloc_array(array, size);
{
	(*array) = (char **)malloc(sizeof(char *) * (size + 1));
	if ((*array) == NULL)
	{
		write(2, "Mimisell: Allocation memory error\n", 35);
		exit(EXIT_FAILURE);
	}
}

void	ms_malloc_str(char **name, int size) // ms_malloc_str(&str, size);
{
	(*name) = malloc(sizeof(char) * (size + 1));
	if ((*name) == NULL)
	{
		write(2, "Mimisell: Allocation memory error\n", 35);
		exit(EXIT_FAILURE);
	}
}

void	ms_malloc_arg(t_arg **arg, int size) //ms_malloc_str(&arg, size);
{
	(*arg) = malloc(sizeof(t_arg) * (size + 1));
	if ((*arg) == NULL)
	{
		write(2, "Mimisell: Allocation memory error\n", 35);
		exit(EXIT_FAILURE);
	}
}

void	ms_malloc_cmd(t_cmd **cmd, int size) //ms_malloc_str(&cmd, size);
{
	(*cmd) = malloc(sizeof(t_cmd) * (size + 1));
	if ((*cmd) == NULL)
	{
		write(2, "Mimisell: Allocation memory error\n", 35);
		exit(EXIT_FAILURE);
	}
}

int	*ms_malloc_arr_int(int **arr_int, int size)
{
	(*arr_int) = (int *)malloc(sizeof(int) * (size + 1));
	if ((*arr_int) == NULL)
	{
		write(2, "Mimisell: Allocation memory error\n", 35);
		exit(EXIT_FAILURE);
	}
	return(*arr_int);
}