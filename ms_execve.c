#include "minishell.h"
 
void	ms_execve(t_cmd *cmd, t_data *data, int i)
{
	pid_t pid;

	ms_check_first_arg(data);
	if (data->num_error != 0 || data->empty_str == YES)
	{
		write (1, "D\n", 2);
		return ;
	}
	if ((pid = fork()) == -1)
		perror("fork error");
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		//printf("cmd = %s\t %s\n", cmd[i].cur_way_cmd, cmd[i].array_arg[0]);
		//printf("cmd = %s\t %s\n", cmd[i].cur_way_cmd, cmd[i].array_arg[0]);
		// if (cmd[i].array_arg[0][0] == '.' && cmd[i].array_arg[0][1] == '/')
		// {
			
		// 	if (execve(cmd[i].cur_way_cmd, cmd[i].array_arg, data->our_env) == -1)
		// 		perror("execve ");
		// }
		// else
		// {
			if (execve(cmd[i].way_cmd, cmd[i].array_arg, data->our_env) == -1)
				perror("execve ");
		// }
		exit (0);
	}
}