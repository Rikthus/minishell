/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:36:26 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/09/27 18:05:14 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_exec(int i)
{
	int	status;

	while (i > 0)
	{
		wait(&status);
		//printf("Status: %d\n", status);
		if (WIFSIGNALED(status))
		{
			//perror("WTERMSIG(status)");
			if (status == 10)
				printf("Bus error: %d\n", WTERMSIG(status));
			else if (status == 11)
				printf("Segmentation fault: %d\n", WTERMSIG(status));
		}
		else if (WIFEXITED(status))
		{
			//printf("Exited normally with code %d\n", WEXITSTATUS(status));
		}
		i--;
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

void	exec(t_token *token, t_envlist *envp)
{
	pid_t		pid;
	t_env_token	env_token;
	int			pipeline[2];
	int			pipetmp[2];
	int			i;

	env_token.token = token;
	env_token.envp = envp;
	env_token.old_stdout = dup(STDOUT_FILENO);
	if (pipe(pipeline) == -1)
		return (perror(""));
	i = 0;
	while (env_token.token)
	{
		pid = fork();
		if (pid < 0)
			return (perror(""));
		if (pid == 0)
			choose_process(&env_token, pipeline, pipetmp, i);
		close_pipes_norm(pipeline, pipetmp, &i);
		env_token.token = env_token.token->next;
	}
	wait_exec(i);
}
