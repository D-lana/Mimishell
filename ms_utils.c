#include "minishell.h"

void	ms_record_char(char **result, char *str, int *r, int *s)
{
	(*result)[(*r)] = str[(*s)];
	(*r)++;
	(*s)++;
}

void	ms_record_str(char **file, char *str, int start, int size_str)
{
	int	i;

	i = 0;
	while(i < size_str)
	{
		(*file)[i] = str[start + i];
		i++;
	}
	(*file)[i] = '\0';
}


