#include "minishell.h"

void	ms_export(t_data *data)
{
	int y;
	char	qm_d;

	y = 0;
	qm_d = DOUBLE_Q_MARK;
	while (y < data->num_env)
	{
		printf("declare -x %s=%c%s%c\n", data->env->key, qm_d,
				data->env->value, qm_d);
		data->env = data->env->next;
		y++;
	}
}

void	ft_cut_list(t_env *cut_list) //, t_env *p_to_struct)
{
	t_env	*tmp;
	t_env	*p_prev;

	tmp = cut_list;
	p_prev = cut_list->prev;
	cut_list = cut_list->next;
	cut_list->prev = p_prev;
	p_prev->next = cut_list;
	tmp->next = NULL;
	tmp->prev = NULL;
	printf("cut\n");
	if (tmp)
	{
		if (tmp->key)
			ms_free_str(&tmp->key);
		if (tmp->value)
			ms_free_str(&tmp->value);
		free(tmp);
	}
}

void	ms_unset(t_data *data, int i)
{
	int y;
	int size_key;

	y = 0;
	while (y < data->num_env)
	{
		size_key = ft_strlen(data->env->key) + 1;
		printf("yes %d\n", y);

		if(ft_strncmp(data->cmd[i].array_arg[1], data->env->key, size_key) == 0)
		{
			printf("yes\n");
			ft_cut_list(data->env);
			// t_env	*tmp;
			// t_env	*p_prev;

			// tmp = data->env;
			// p_prev = data->env->prev;
			// data->env = data->env->next;
			// data->env->prev = p_prev;
			// p_prev->next = data->env;
			// tmp->next = NULL;
			// tmp->prev = NULL;
			// printf("cut\n");
			// if (tmp)
			// {
			// 	if (tmp->key)
			// 		ms_free_str(&tmp->key);
			// 	if (tmp->value)
			// 		ms_free_str(&tmp->value);
			// 	free(tmp);
			// }
			//ft_cut_list(data->env);
			data->num_env--;
			return ;
		}
		printf("s %s\n", data->env->key);
		data->env = data->env->next;
		y++;
	}
}

// void	ft_create_env_list(t_env *env, char *key, char *value)
// {
// 	t_env	*tmp;

// 	tmp = malloc(sizeof(t_env));
// 	if (!tmp)
// 		ft_error();
// 	tmp->key = key;
// 	tmp->value = value;
// 	if (env == 0)
// 	{
// 		tmp->prev = tmp;
// 		tmp->next = tmp;
// 	}
// 	if (env != 0)
// 	{
// 		tmp->prev = env->prev;
// 		env->prev->next = tmp;
// 		tmp->next = env;
// 		env->prev = tmp;
// 	}
// 	env = tmp;
// }

// void	ft_rotate_list(t_env *points)
// {
// 	if (points->count_a > 1)
// 		points->a = points->a->next;
// 	if (points->checker == 0)
// 		write (1, "ra\n", 3);
// }


// void    ms_env(t_data *data, char **env)
// {
//     int y;
//     int x;
//     y = 0;
//     x = 0;
//     //t_data *new = data;
//     //const char *env;
//     //env = getenv("All");
//     while (env[y] != 0)
//         y++;
//     ms_malloc_array(&data->our_env, y);
//     y = 0;
//     while (env[y] != 0)
//     {
//         while (env[y][x] != '\0')
//         {
//             x++;
//         }
//         ms_malloc_str(&data->our_env[y], x);
//         ms_record_str(&data->our_env[y], env[y], 0, x);
//         printf("%s\n", data->our_env[y]);
//         y++;
//         x = 0;
//     }
// }