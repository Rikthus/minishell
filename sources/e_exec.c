/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:36:26 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/10/03 21:26:17 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	wait_exec(int i)
{
	int	status;

	while (i > 0)
	{
		wait(&status);
		if (WIFSIGNALED(status))
		{
			if (status == 10)
			{
				g_shell.exit_status = WTERMSIG(status);
				printf("Bus error: %d\n", g_shell.exit_status);
			}
			else if (status == 11)
			{
				g_shell.exit_status = WTERMSIG(status);
				printf("Segmentation fault: %d\n", g_shell.exit_status);
			}
		}
		else if (WIFEXITED(status))
			g_shell.exit_status = WEXITSTATUS(status);
		i--;
	}
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
	int			i;

	e_t.token = token;
	e_t.envp = envp;
	e_t.old_stdout = dup(STDOUT_FILENO);
	if (pipe(pipeline) == -1)
		return (perror_msg(0));
	i = 0;
	while (e_t.token)
	{
		if (i == 0 && !e_t.token->next && is_builtin(e_t.token->cmd[0]) != 0)
		{
			redirection(&e_t);
			if (choose_builtin(e_t.token->cmd[0], &e_t) == -1)
				return (-1);
			if (dup2(e_t.old_stdout, STDOUT_FILENO) == -1)
				return (perror_msg(0));
		}
		else
		{
			signal_mini(EXEC);
			pid = fork();
			if (pid < 0)
				return (perror_msg(0));
			if (pid == 0)
			{
				if (e_t.token->cmd[0] && is_builtin(e_t.token->cmd[0]) != 0)
					choose_process_bltn(&e_t, pipeline, pipetmp, i);
				else
					choose_process(&e_t, pipeline, pipetmp, i);
			}
		}
		close_pipes_norm(pipeline, pipetmp, &i);
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
