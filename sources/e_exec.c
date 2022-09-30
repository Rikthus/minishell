/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:36:26 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/09/30 15:58:51 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_exec(int i[2])
{
	int	u;

	u = i[COUNT_ALL] - i[COUNT_BUILTS];
	while (u > 0)
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
		u--;
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

static	int	is_builtin(char *str)
{
	if (ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "exit") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "export") == 0 || ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "echo") == 0)
		return (1);
	else
		return (0);
}

/* int	choose_builtin(char *str, t_env_token *env_token)
{
	int	ret;

	ret = 0;
	// if (ft_strcmp(str, "cd") == 0)
	// 	ret = bltn_cd();
	else if (ft_strcmp(str, "pwd") == 0)
		ret = bltn_pwd(env_token->cmd, env_token);
	// else if (ft_strcmp(str, "exit") == 0)
	// 	ret = bltn_exit();
	else if (ft_strcmp(str, "env") == 0)
		ret = bltn_env(env_token->cmd, env_token);
	else if (ft_strcmp(str, "export") == 0)
		ret = bltn_export(env_token->cmd, env_token);
	else if (ft_strcmp(str, "unset") == 0)
		ret = bltn_unset(env_token->cmd, env_token);
	else if (ft_strcmp(str, "echo") == 0)
		ret = bltn_echo(env_token->cmd);
	return (ret);
} */

int	exec(t_token *token, t_envlist *envp)
{
	pid_t		pid;
	t_env_token	env_token;
	int			pipeline[2];
	int			pipetmp[2];
	int			i[2];

	env_token.token = token;
	env_token.envp = envp;
	env_token.old_stdout = dup(STDOUT_FILENO);
	if (pipe(pipeline) == -1)
		return (0);
	i[COUNT_ALL] = 0;
	i[COUNT_BUILTS] = 0;
	while (env_token.token)
	{
		// EXEC BUILTINS if ()
		if (is_builtin(env_token.token->cmd[i[COUNT_ALL]]) != 0)
		{
			if (choose_process_bltn(&env_token, pipeline, pipetmp, &i[0], &i[1]) == -1)
				return (-1);
		}
		else
		{
			signal_exec();
			pid = fork();
			if (pid < 0)
				return (0);
			if (pid == 0)
			{
				choose_process(&env_token, pipeline, pipetmp, i[COUNT_ALL]);
			}
		}
		close_pipes_norm(pipeline, pipetmp, &i[COUNT_ALL]);
		env_token.token = env_token.token->next;
	}
	wait_exec(i);
	close(pipeline[0]);
	close(pipeline[1]);
	close(pipetmp[1]);
	signal_mini();
	return (1);
}
