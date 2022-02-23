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

static int  check_str(t_data *data, char **arr_p, int i, int n)
{
    int     find_cmd;
    char    *str_slesh;
    char    *str_way;
    find_cmd = 0;
    str_way = NULL;
    // оттестить если первый аргумент редирект
    while (arr_p[i])
    {
        str_slesh = add_slesh(arr_p, i, 0);
        str_way = ft_strjoin(str_slesh, data->cmd[n].array_arg[0]);
        ms_free_str(&str_slesh); // change
        if (!access (str_way, 1))
        {
            find_cmd = -1; // нашла команду
            data->cmd[n].way_cmd = ft_strdup(str_way); // отфришить где-нибудь в конце
            break ;
        }
        else
            find_cmd++;
        ms_free_str(&str_way); // changed free
        i++;
    }
    return (find_cmd);
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
