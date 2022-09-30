/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:36:26 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/09/30 03:28:56 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_exec(int i)
{
	while (i > 0)
	{
		wait(&g_exit_status);
		//printf("Status: %d\n", status);
		if (WIFSIGNALED(g_exit_status))
		{
			//perror("WTERMSIG(status)");
			if (g_exit_status == 10)
				printf("Bus error: %d\n", WTERMSIG(g_exit_status));
			else if (g_exit_status == 11)
				printf("Segmentation fault: %d\n", WTERMSIG(g_exit_status));
		}
		else if (WIFEXITED(g_exit_status))
		{
			//printf("Exited normally with code %d\n", WEXITSTATUS(status));
		}
		i--;
	}
	/* while (i > 0)
	{
		wait(NULL);
		i--;
	} */
	//while (--i >= 0)
	//	wait(NULL);
}

void	close_pipes_norm(int *pipeline, int *pipetmp, int *i)
{
	if (i > 0)
		close(pipetmp[0]);
	close(pipeline[1]);
	pipetmp[0] = pipeline[0];
	if (pipe(pipeline) < 0)
		return (perror("pipe"));
	*i = *i + 1;
}

//BUILTINS
// static	int	is_builtin(char *str)
// {
// 	int	ret;

// 	ret = 0;
// 	if (ft_strcmp(str, "cd") == 0)
// 		ret = choose_process_bltn();
// 	else if (ft_strcmp(str, "pwd") == 0)
// 		ret = choose_process_bltn();
// 	else if (ft_strcmp(str, "exit") == 0)
// 		ret = choose_process_bltn();
// 	else if (ft_strcmp(str, "env") == 0)
// 		ret = choose_process_bltn();
// 	else if (ft_strcmp(str, "export") == 0)
// 		ret = choose_process_bltn();
// 	else if (ft_strcmp(str, "unset") == 0)
// 		ret = choose_process_bltn();
// 	else if (ft_strcmp(str, "echo") == 0)
// 		ret = choose_process_bltn();
// 	return (ret);
// }

int	exec(t_token *token, t_envlist *envp)
{
	pid_t		pid;
	t_env_token	env_token;
	int			pipeline[2];
	int			pipetmp[2];
	int			i;

	env_token.token = token;
	env_token.envp = envp;
	env_token.old_stdout = dup(STDOUT_FILENO);
	if (pipe(pipeline) == -1)
		return (0);
	i = 0;
	while (env_token.token)
	{
		// EXEC BUILTINS if ()
		signal_exec();
		pid = fork();
		if (pid < 0)
			return (0);
		if (pid == 0)
		{
			choose_process(&env_token, pipeline, pipetmp, i);
		}
		close_pipes_norm(pipeline, pipetmp, &i);
		env_token.token = env_token.token->next;
	}
	wait_exec(i);
	signal_mini();
	return (1);
}
