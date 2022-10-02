/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 03:02:46 by tulipe            #+#    #+#             */
/*   Updated: 2022/10/02 16:54:22 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	choose_builtin(char *str, t_env_token *env_token)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(str, "cd") == 0)
		ret = ft_cd(env_token->token->cmd, &(env_token->envp));
	if (ft_strcmp(str, "pwd") == 0)
		ret = ft_pwd(env_token->token->cmd, env_token->envp[0]);
	// else if (ft_strcmp(str, "exit") == 0)
	// 	ret = ft_exit();
	else if (ft_strcmp(str, "env") == 0)
		ret = ft_env(env_token->token->cmd, env_token->envp[0]);
	else if (ft_strcmp(str, "export") == 0)
		ret = ft_export(env_token->token->cmd, env_token->envp);
	else if (ft_strcmp(str, "unset") == 0)
		ret = ft_unset(env_token->token->cmd, env_token->envp);
	else if (ft_strcmp(str, "echo") == 0)
		ret = ft_echo(env_token->token->cmd);
	if (ret == EXIT_SUCCESS)
		g_exit_status = 0;
	else if (ret == EXIT_FAILURE)
		g_exit_status = 1;
	else
		g_exit_status = -1; // malloc error number ?
	return (ret);
}

static	int	inter_process_bltn(t_env_token *e_t, int *pipeline, int *pipetmp)
{
	if (dup2(pipetmp[0], STDIN_FILENO) == -1)
		return (-1);
	if (dup2(pipeline[1], STDOUT_FILENO) == -1)
		return (-1);
	close(pipetmp[0]);
	close(pipeline[1]);
	close(pipeline[0]);
	redirection(e_t);
	if (choose_builtin(e_t->token->cmd[0], e_t) == -1)
		return (-1);
	return (0);
}

static	int	last_process_bltn(t_env_token *e_t, int *pipetmp)
{
	if (dup2(pipetmp[0], STDIN_FILENO) == -1)
		return (-1);
	close(pipetmp[0]);
	close(pipetmp[1]);
	redirection(e_t);
	if (dup2(e_t->old_stdout, 1) == -1)
		return (-1);
	if (choose_builtin(e_t->token->cmd[0], e_t) == -1)
		return (-1);
	return (0);
}

static	int	first_process_bltn(t_env_token *e_t, int *pipeline)
{
	(void) pipeline;
	if (e_t->token->next == NULL)
	{
		redirection(e_t);
		if (choose_builtin(e_t->token->cmd[0], e_t) == -1)
			return (-1);
	}
	else
	{
		if (dup2(pipeline[1], STDOUT_FILENO) == -1)
			return (-1);
		close(pipeline[1]);
		close(pipeline[0]);
		redirection(e_t);
		if (choose_builtin(e_t->token->cmd[0], e_t) == -1)
			return (-1);
	}
	return (0);
}

int	choose_process_bltn(t_env_token *env_token, int *pipeline, int *pipetmp, int *i, int *u)
{
	if (*i == 0)
	{
		*u += 1;
		return (first_process_bltn(env_token, pipeline));
	}
	else if (env_token->token->next == NULL)
	{
		*u += 1;
		return (last_process_bltn(env_token, pipetmp));
	}
	else
	{
		*u += 1;
		return (inter_process_bltn(env_token, pipeline, pipetmp));
	}
	return (0);
}