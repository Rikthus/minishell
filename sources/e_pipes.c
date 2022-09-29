/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:20:33 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/09/29 15:04:46 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	inter_process(t_env_token *e_t, int *pipeline, int *pipetmp, char *g_p)
{
	if (dup2(pipetmp[0], STDIN_FILENO) == -1)
		exit(1);
	if (dup2(pipeline[1], STDOUT_FILENO) == -1)
		exit(1);
	close(pipetmp[0]);
	close(pipeline[1]);
	close(pipeline[0]);
	redirection(e_t);
	if (execve(g_p, e_t->token->cmd, e_t->env) == -1)
	{
		perror("Could not execute execve middle process");
		exit(0);
	}
}

void	last_process(t_env_token *e_t, int *pipetmp, char *good_path)
{
	if (dup2(pipetmp[0], STDIN_FILENO) == -1)
		exit(1);
	close(pipetmp[0]);
	redirection(e_t);
	if (dup2(e_t->old_stdout, 1) == -1)
		return (perror(""));
	if (execve(good_path, e_t->token->cmd, e_t->env) == -1)
	{
		perror("Could not execute execve last process");
		exit(0);
	}
}

void	first_process(t_env_token *e_t, int *pipeline, char *good_path)
{
	if (e_t->token->next == NULL)
	{
		redirection(e_t);
		if (execve(good_path, e_t->token->cmd, e_t->env) == -1)
		{
			perror("Could not execute execve");
			exit(0);
		}
	}
	else
	{
		if (dup2(pipeline[1], STDOUT_FILENO) == -1)
			exit(1);
		close(pipeline[1]);
		close(pipeline[0]);
		redirection(e_t);
		if (execve(good_path, e_t->token->cmd, e_t->env) == -1)
		{
			perror("Could not execute execve first process");
			exit(0);
		}
	}
}

void	choose_process(t_env_token *e_t, int *pipeline, int *pipetmp, int i)
{
	char	*good_path;
	char	**env;

	if (e_t->envp->env_var)
	{
		good_path = prepare_commands(e_t->token, e_t->envp);
		if (!good_path)
			return (perror(""));
		env = custom_envp(e_t->envp);
		if (!env)
			return (perror(""));
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
