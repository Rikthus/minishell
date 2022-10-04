/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 03:02:46 by tulipe            #+#    #+#             */
/*   Updated: 2022/10/04 14:03:10 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	choose_builtin(char *str, t_env_token *env_token)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(str, "cd") == 0)
		ret = ft_cd(env_token->token->cmd, env_token->envp);
	if (ft_strcmp(str, "pwd") == 0)
		ret = ft_pwd(env_token->token->cmd, env_token->envp[0]);
	else if (ft_strcmp(str, "exit") == 0)
		ret = ft_exit(env_token->token->cmd);
	else if (ft_strcmp(str, "env") == 0)
		ret = ft_env(env_token->token->cmd, env_token->envp[0]);
	else if (ft_strcmp(str, "export") == 0)
		ret = ft_export(env_token->token->cmd, env_token->envp);
	else if (ft_strcmp(str, "unset") == 0)
		ret = ft_unset(env_token->token->cmd, env_token->envp);
	else if (ft_strcmp(str, "echo") == 0)
		ret = ft_echo(env_token->token->cmd);
	if (ret == EXIT_SUCCESS)
		g_shell.exit_status = EXIT_SUCCESS;
	else if (ret == EXIT_FAILURE)
		g_shell.exit_status = EXIT_FAILURE;
	else if (ret != -1)
		g_shell.exit_status = ret;
	return (ret);
}

static	void	inter_process_bltn(t_env_token *e_t,
		int *pipeline, int *pipetmp)
{
	if (dup2(pipetmp[0], STDIN_FILENO) == -1)
		exit (-1);
	if (dup2(pipeline[1], STDOUT_FILENO) == -1)
		exit (-1);
	close(pipetmp[0]);
	close(pipeline[1]);
	close(pipeline[0]);
	redirection(e_t);
	if (choose_builtin(e_t->token->cmd[0], e_t) == 1)
		exit (1);
	exit (0);
}

static	void	last_process_bltn(t_env_token *e_t, int *pipetmp)
{
	if (dup2(pipetmp[0], STDIN_FILENO) == -1)
		exit (-1);
	close(pipetmp[0]);
	close(pipetmp[1]);
	redirection(e_t);
	if (dup2(e_t->old_stdout, 1) == -1)
		exit (-1);
	if (choose_builtin(e_t->token->cmd[0], e_t) == 1)
		exit (1);
	exit (0);
}

static	void	first_process_bltn(t_env_token *e_t, int *pipeline)
{
	if (e_t->token->next == NULL)
	{
		redirection(e_t);
		if (choose_builtin(e_t->token->cmd[0], e_t) == 1)
			exit (1);
	}
	else
	{
		if (dup2(pipeline[1], STDOUT_FILENO) == -1)
			exit (-1);
		close(pipeline[1]);
		close(pipeline[0]);
		redirection(e_t);
		if (choose_builtin(e_t->token->cmd[0], e_t) == 1)
			exit (1);
	}
	exit (0);
}

void	choose_process_bltn(t_env_token *env_token,
		int *pipeline, int *pipetmp, int i)
{
	if (i == 0)
		first_process_bltn(env_token, pipeline);
	else if (env_token->token->next == NULL)
		last_process_bltn(env_token, pipetmp);
	else
		inter_process_bltn(env_token, pipeline, pipetmp);
}
