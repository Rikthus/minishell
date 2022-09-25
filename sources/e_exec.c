/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charline <charline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:33:36 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/09/25 22:51:05 by charline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* struct	s_command
{
	char	*path; // ex: /bin/ls
	char	**envp;
	char	**argv;	
}; */

void	inter_process(t_token *token, char **envp, int *pipeline, int *pipetmp, char *good_path)
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

void choose_process(t_token *token, t_envlist *envp, int *pipeline, int *pipetmp, int i)
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
			choose_process(token, envp, pipeline, pipetmp, i);
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
}

/* void	exec(t_token *token, char **envp)
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
			choose_process(token, envp, pipeline, pipetmp, i);
		if (i > 0)
			close(pipetmp[0]);
		close(pipeline[1]);
		pipetmp[0] = pipeline[0];
		if (pipe(pipeline) < 0)
			return (perror("pipe"));
		i++;
		token = token->next;
	}
	while (--i >= 0)
		wait(NULL);
} */

/* void	exec(t_token *token, char **envp)
{
	pid_t	pid;
	char	*good_path;
	int		pipeline[2];
	int		pipetmp[2];
	int		i;

	if (pipe(pipeline) == -1)
		return ;
	i = 0;
	while (token)
	{
		pid = fork();
		if (pid < 0)
			return ;
		if (pid == 0)
		{
			good_path = prepare_commands(token);
			if (!good_path)
			{
				perror("");
				return ;
			}
			if (i == 0)
				first_process(token, envp, pipeline, good_path);
			else if (token->next == NULL)
				last_process(token, envp, pipetmp, good_path);
			else
			{
				inter_process(token, envp, pipeline, pipetmp, good_path);
			}
		}
		if (i > 0)
			close(pipetmp[0]);
		close(pipeline[1]);
		pipetmp[0] = pipeline[0];
		if (pipe(pipeline) < 0)
		{
			perror("pipe");
			return ;
		}
		i++;
		token = token->next;
	}
	while (--i >= 0)
	{
		wait(NULL);
	}
} */

/* void	exec(t_token *token, char **envp)
{
	pid_t	pid;
	char	*good_path;
	int		pipeline[2];
	int		pipetmp[2];
	int		i;

	good_path = NULL;
	if (pipe(pipeline) == -1)
		return ;
	i = 0;
	while (token)
	{
		pid = fork();
		if (pid < 0)
			return ;
		if (pid == 0)
		{
			if (find_absolute_path(token->cmd) == -1)
				good_path = token->cmd[0];
			else if (find_absolute_path(token->cmd) == 0)
				good_path = exec_cmd(token->cmd);
			if (!good_path)
			{
				perror("");
				return ;
			}
			if (i == 0)
			{
				if (token->next == NULL)
				{
					if (execve(good_path, token->cmd, envp) == -1)
					{
						perror("Could not execute execve last");
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
						perror("Could not execute execve first");
						exit(0);
					}
				}
			}
			else if (token->next == NULL)
			{
				if (dup2(pipetmp[0], STDIN_FILENO) == -1)
					exit(1);
				close(pipetmp[0]);
				if (execve(good_path, token->cmd, envp) == -1)
				{
					perror("Could not execute execve last");
					exit(0);
				}
			}
			else
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
					perror("Could not execute execve");
					exit(0);
				}
			}
		}
		if (i > 0)
			close(pipetmp[0]);
		close(pipeline[1]);
		pipetmp[0] = pipeline[0];
		if (pipe(pipeline) < 0)
		{
			perror("pipe");
			return ;
		}
		i++;
		token = token->next;
	}
	while (--i >= 0)
	{
		wait(NULL);
	}
} */
