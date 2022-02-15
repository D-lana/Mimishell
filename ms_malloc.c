#include "minishell.h"

void	ms_free_str(char **tmp_str);
void	ms_malloc_str(char **name, int size);
void	ms_malloc_arg(t_arg **arg, int size);
void	ms_malloc_cmd(t_cmd **cmd, int size);

void	ms_free_str(char **tmp_str) // ms_free_str(&str);
{
	char *tmp;

	tmp = *tmp_str;
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	*tmp_str = tmp;
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