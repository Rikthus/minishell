/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:20:33 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/10/04 16:39:57 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	inter_process(t_env_token *e_t,
		int *pipeline, int *pipetmp, char *g_p)
{
	if (dup2(pipetmp[0], STDIN_FILENO) == -1)
		exit(1);
	if (dup2(pipeline[1], STDOUT_FILENO) == -1)
		exit(1);
	close(pipetmp[0]);
	close(pipeline[1]);
	close(pipeline[0]);
	redirection(e_t);
	if (e_t->token->cmd[0] && execve(g_p, e_t->token->cmd, e_t->env) == -1)
		perror("");
	else
		exit(0);
	exit(255);
}

static	void	last_process(t_env_token *e_t, int *pipetmp, char *good_path)
{
	if (dup2(pipetmp[0], STDIN_FILENO) == -1)
		exit(1);
	close(pipetmp[0]);
	redirection(e_t);
	if (dup2(e_t->old_stdout, 1) == -1)
		return (perror(""));
	if (e_t->token->cmd[0]
		&& execve(good_path, e_t->token->cmd, e_t->env) == -1)
		perror("");
	else
		exit(0);
	exit(255);
}

static	void	first_process(t_env_token *e_t, int *pipeline, char *good_path)
{
	if (e_t->token->next == NULL)
	{
		redirection(e_t);
		if (e_t->token->cmd[0]
			&& execve(good_path, e_t->token->cmd, e_t->env) == -1)
			perror("");
		else
			exit(0);
	}
	else
	{
		if (dup2(pipeline[1], STDOUT_FILENO) == -1)
			exit(1);
		close(pipeline[1]);
		close(pipeline[0]);
		redirection(e_t);
		if (e_t->token->cmd[0]
			&& execve(good_path, e_t->token->cmd, e_t->env) == -1)
			perror("");
		else
			exit(255);
	}
	exit(0);
}

void	choose_process(t_env_token *e_t, int *pipeline, int *pipetmp, int i)
{
	t_envlist	*env_cpy;
	char		*good_path;
	char		**env;

	env_cpy = e_t->envp[0];
	if (env_cpy && e_t->token->cmd[0])
	{
		good_path = prepare_commands(e_t->token, env_cpy);
		if (!good_path)
			exit(127);
		env = custom_envp(env_cpy);
		if (!env)
			exit(-1);
		e_t->env = env;
	}
	else
		good_path = NULL;
	if (i == 0)
		first_process(e_t, pipeline, good_path);
	else if (e_t->token->next == NULL)
		last_process(e_t, pipetmp, good_path);
	else
		inter_process(e_t, pipeline, pipetmp, good_path);
}
