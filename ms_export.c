#include "minishell.h"

void	ms_export(t_data *data, int i);

void	ms_print_sort_export(t_data *data, int y)
{
	int		x;
	char	qm_d;

	x = 0;
	qm_d = DOUBLE_Q_MARK;
	write(1, "declare -x ", 12);
	while (data->our_env[y][x] != '=' && data->our_env[y][x] != '\0')
	{
		write(1, &data->our_env[y][x], 1);
		x++;
	}
	if (data->our_env[y][x] != '\0')
	{
		write(1, "=", 1);
		x++;
		write(1, &qm_d, 1);
		while (data->our_env[y][x] != '\0')
		{
			write(1, &data->our_env[y][x], 1);
			x++;
		}
		write(1, &qm_d, 1);
	}
	write(1, "\n", 1);
}

int	ft_strncmp_by_env(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*t1;
	unsigned char	*t2;

	t1 = (unsigned char *) s1;
	t2 = (unsigned char *) s2;
	i = 0;
	while ((t1[i] != '\0' || t2[i] != '\0') && t2[i] != '=' && t1[i] != '=')
	{	
		if (t1[i] != t2[i])
			return (t1[i] - t2[i]);
		i++;
	}
	if ((t1[i] != '\0' || t2[i] != '\0') && t2[i] != '=' && t1[i] != '=')
		return (t1[i] - t2[i]);
	return (0);
}

void	ms_sort_env(t_data *data, int y, int **sort)
{
	int	i;
	int	difference;
	int	first;

	i = 0;
	difference = 0;
	first = YES;
	i = 0;
	while (i < data->num_env)
	{
		if ((*sort)[i] != YES)
		{
			difference = ft_strncmp_by_env(data->our_env[y], data->our_env[i]);
			if (difference > 0)
				first = NO;
		}
		i++;
	}
	if (first == YES && (*sort)[y] != YES)
	{
		(*sort)[y] = YES;
		ms_print_sort_export(data, y);
	}
}

int	ms_check_sorted(int **sort, t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->num_env)
	{
		if ((*sort)[i] == NO)
			return (NO);
		i++;
	}
	return (YES);
}

void	ms_recurs_sort(t_data *data, int **sort)
{
	int	end;
	int	y;

	y = 0;
	end = 0;
	while (y < data->num_env)
	{
		ms_sort_env(data, y, sort);
		y++;
		if (y == data->num_env)
		{
			end = ms_check_sorted(sort, data);
			if (end == NO)
				ms_recurs_sort(data, sort);
		}
	}
}

void	ms_export(t_data *data, int i)
{
	int		y;
	int		*sort;

	y = 0;
	if (data->cmd[i].array_arg[1] != NULL)
	{
		ms_add_env_variable(data, i);
		return ;
	}
	*sort = *ms_malloc_arr_int(&sort, data->num_env);
	while (sort[y] < data->num_env)
	{
		sort[y] = NO;
		y++;
	}
	ms_recurs_sort(data, &sort);
	ms_free_int_arr(&sort);
}
