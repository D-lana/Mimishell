
#include "minishell.h"

static char	*add_slesh(char **arr_p, int i, int j)
{
	char	*str_slesh;
	str_slesh = NULL;
	ms_malloc_str(&str_slesh, ft_strlen(arr_p[i]) + 1);
	while (arr_p[i][j] != '\0')
	{
		str_slesh[j] = arr_p[i][j];
		j++;
	}
	str_slesh[j] = '/';
	str_slesh[j + 1] = '\0';
	return (str_slesh);
}



void	ms_check_first_arg(t_data *data)
{
	const char	*p;
	char		**arr_p;
	int			i;
	int			n;
	int			find_cmd;

	i = 0;
	n = 0;
	find_cmd = 0;
	if (data->num_error != 0 || data->empty_str == YES)
		return ;
	p = getenv("PATH");
	arr_p = ft_split(p, ':');
	while (n < data->num_cmd)
	{
		find_cmd = check_str(data, arr_p, i, n);
		if (find_cmd > 0)
		{
			data->num_error = ERR_CMD;
			printf("Mimishell: %s: command not found\n",
				data->cmd[n].array_arg[0]);
		}
		n++;
	}
}
