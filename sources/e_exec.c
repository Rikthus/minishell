/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:36:26 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/10/04 19:48:36 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static	int	exec_fork(t_env_token	*e_t, int	*pipeline, int *pipetmp, int *i)
{
	pid_t	pid;

	signal_mini(EXEC);
	pid = fork();
	if (pid < 0)
		return (perror_msg(0));
	if (pid == 0)
	{
		if (e_t->token->cmd[0] && is_builtin(e_t->token->cmd[0]) != 0)
			choose_process_bltn(e_t, pipeline, pipetmp, i);
		else
			choose_process(e_t, pipeline, pipetmp, i);
	}
	return (1);
}

static	int	exec_solo_builtin(t_env_token *e_t)
{
	if (built_redirection(e_t) == -1)
		return (1);
	if (choose_builtin(e_t->token->cmd[0], e_t) == -1)
	{
		g_shell.exit_status = -1;
		return (0);
	}
	if (dup2(e_t->old_stdout, STDOUT_FILENO) == -1)
		return (perror_msg(0));
	return (1);
}

static	int	choose_exec_type(t_env_token *e_t,
			int *pipeline, int *pipetmp, int *i)
{
	int	ret;

	ret = 1;
	if (e_t->token->cmd[0] && *i == 0 && !e_t->token->next
		&& is_builtin(e_t->token->cmd[0]) != 0)
	{
		ret = exec_solo_builtin(e_t);
		if (ret != 1)
			return (ret);
	}
	else
	{
		if (exec_fork(e_t, pipeline, pipetmp, i) == 0)
			return (0);
	}
	return (ret);
}

int	exec(t_token *token, t_envlist **envp)
{
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
		if (choose_exec_type(&e_t, pipeline, pipetmp, &i) == 0)
			return (0);
		close_pipes_norm(pipeline, pipetmp, &i);
		e_t.token = e_t.token->next;
	}
	close_remaining_fd(i, pipeline, pipetmp, token);
	return (1);
}
