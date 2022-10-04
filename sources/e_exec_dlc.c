/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec_dlc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:07:35 by maxperei          #+#    #+#             */
/*   Updated: 2022/10/04 20:57:01 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	close_heredoc_pipes(t_token *token)
{
	int	i;
	int	nb_heredoc;

	while (token)
	{
		i = 0;
		nb_heredoc = 0;
		while (token->redir[i] != NO_REDIR)
		{
			if (token->redir[i] == HEREDOC)
				nb_heredoc++;
			i++;
		}
		if (nb_heredoc > 0)
		{
			i = 0;
			while (i < nb_heredoc)
			{
				close(token->hd_pipe[i][0]);
				i++;
			}
		}
		token = token->next;
	}
}

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

void	execve_error(t_env_token *e_t)
{
	ft_putstr_fd("Maxine ❤️: ", 2);
	ft_putstr_fd(e_t->token->cmd[0], 2);
	perror(" ");
	exit(127);
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

void	close_remaining_fd(int i, int *pipeline, int *pipetmp, t_token *token)
{
	wait_exec(i);
	close(pipeline[0]);
	close(pipeline[1]);
	close(pipetmp[0]);
	close_heredoc_pipes(token);
	signal_mini(BASIC);
}
