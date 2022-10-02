/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:36:26 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/10/02 16:43:19 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	wait_exec(int i[2])
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

static	void	close_pipes_norm(int *pipeline, int *pipetmp, int *i)
{
	if (i > 0)
		close(pipetmp[0]);
	close(pipeline[1]);
	pipetmp[0] = pipeline[0];
	if (pipe(pipeline) < 0)
		return (perror("pipe"));
	*i = *i + 1;
}

static	void	close_heredoc_pipes(t_token *token)
{
	int	i;

	while (token)
	{
		i = 0;
		if (token->hd_pipe)
		{
			while (token->hd_pipe[i])
			{
				close(token->hd_pipe[i][0]);
				i++;
			}
		}
		token = token->next;
	}
}

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

int	exec(t_token *token, t_envlist **envp)
{
	pid_t		pid;
	t_env_token	e_t;
	int			pipeline[2];
	int			pipetmp[2];
	int			i[2];

	e_t.token = token;
	e_t.envp = envp;
	e_t.old_stdout = dup(STDOUT_FILENO);
	if (pipe(pipeline) == -1)
		return (0);
	i[COUNT_ALL] = 0;
	i[COUNT_BUILTS] = 0;
	while (e_t.token)
	{
		if (e_t.token->cmd[0] && is_builtin(e_t.token->cmd[0]) != 0)
		{
			if (choose_process_bltn(&e_t, pipeline, pipetmp, &i[0], &i[1]) == -1)
				return (-1);
		}
		else
		{
			signal_mini(EXEC);
			pid = fork();
			if (pid < 0)
				return (0);
			if (pid == 0)
				choose_process(&e_t, pipeline, pipetmp, i[COUNT_ALL]);
		}
		close_pipes_norm(pipeline, pipetmp, &i[COUNT_ALL]);
		e_t.token = e_t.token->next;
	}
	wait_exec(i);
	close(pipeline[0]);
	close(pipeline[1]);
	close(pipetmp[0]);
	close_heredoc_pipes(token);
	signal_mini(BASIC);
	return (1);
}
