/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charline <charline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:36:26 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/09/27 00:26:15 by charline         ###   ########.fr       */
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

	good_path = prepare_commands(e_t->token, e_t->envp);
	if (!good_path)
		return (perror(""));
	env = custom_envp(e_t->envp);
	if (!env)
		return (perror(""));
	e_t->env = env;
	if (i == 0)
		first_process(e_t, pipeline, good_path);
	else if (e_t->token->next == NULL)
		last_process(e_t, pipetmp, good_path);
	else
		inter_process(e_t, pipeline, pipetmp, good_path);
}

void	wait_norm_exec(int i)
{
	while (i > 0)
	{
		wait(NULL);
		i--;
	}
	//while (--i >= 0)
	//	wait(NULL);
}

void	exec(t_token *token, t_envlist *envp)
{
	pid_t		pid;
	t_env_token	env_token;
	int			pipeline[2];
	int			pipetmp[2];
	int			i;

	env_token.token = token;
	env_token.envp = envp;
	if (pipe(pipeline) == -1)
		return (perror(""));
	i = 0;
	while (env_token.token)
	{
		pid = fork();
		if (pid < 0)
			return (perror(""));
		if (pid == 0)
		{
			redirection(&env_token);
			choose_process(&env_token, pipeline, pipetmp, i);
		}
		if (i > 0)
			close(pipetmp[0]);
		close(pipeline[1]);
		pipetmp[0] = pipeline[0];
		if (pipe(pipeline) < 0)
			return (perror("pipe"));
		i++;
		env_token.token = env_token.token->next;
	}
	wait_norm_exec(i);
}

/* void	inter_process(t_token *token, char **envp, int *pipeline, int *pipetmp, char *good_path)
{
	if (dup2(pipetmp[0], STDIN_FILENO) == -1)
		exit(1);
	if (dup2(pipeline[1], STDOUT_FILENO) == -1)
		exit(1);
	close(pipetmp[0]);
	close(pipeline[1]);
	close(pipeline[0]);
	if (execve(good_path, token->cmd, envp) == -1)
	{
		perror("Could not execute execve middle process");
		exit(0);
	}
}

void	last_process(t_token *token, char **envp, int *pipetmp, char *good_path)
{
	if (dup2(pipetmp[0], STDIN_FILENO) == -1)
		exit(1);
	close(pipetmp[0]);
	if (execve(good_path, token->cmd, envp) == -1)
	{
		perror("Could not execute execve last process");
		exit(0);
	}
}

void	first_process(t_token *token, char **envp, int *pipeline, char *good_path)
{
	if (token->next == NULL)
	{
		if (execve(good_path, token->cmd, envp) == -1)
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
		if (execve(good_path, token->cmd, envp) == -1)
		{
			perror("Could not execute execve first process");
			exit(0);
		}
	}
}

void	choose_process(t_token *token, t_envlist *envp, int *pipeline, int *pipetmp, int i)
{
	char	*good_path;
	char	**env;

	good_path = prepare_commands(token, envp);
	if (!good_path)
		return (perror(""));
	env = custom_envp(envp);
	if (!env)
		return (perror(""));
	if (i == 0)
		first_process(token, env, pipeline, good_path);
	else if (token->next == NULL)
		last_process(token, env, pipetmp, good_path);
	else
		inter_process(token, env, pipeline, pipetmp, good_path);
}

void	wait_norm_exec(int i)
{
	while (i > 0)
	{
		wait(NULL);
		i--;
	}
	//while (--i >= 0)
	//	wait(NULL);
}

void	exec(t_token *token, t_envlist *envp)
{
	pid_t	pid;
	int		pipeline[2];
	int		pipetmp[2];
	int		i;

	if (pipe(pipeline) == -1)
		return (perror(""));
	i = 0;
	while (token)
	{
		pid = fork();
		if (pid < 0)
			return (perror(""));
		if (pid == 0)
		{
			//redir avec boucle
			choose_process(token, envp, pipeline, pipetmp, i);
		}
		if (i > 0)
			close(pipetmp[0]);
		close(pipeline[1]);
		pipetmp[0] = pipeline[0];
		if (pipe(pipeline) < 0)
			return (perror("pipe"));
		i++;
		token = token->next;
	}
	wait_norm_exec(i);
} */
