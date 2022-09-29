/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:16:07 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/09/29 15:59:47 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_infile(t_env_token *e_t, int i)
{
	int	fd;

	fd = open(e_t->token->target[i], O_RDONLY);
	if (fd < 0)
	{
		//perror(target[i]);
		return ;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		return (perror(""));
	}
	close(fd);
}

void	redir_append(t_env_token *e_t, int i)
{
	int	fd;

	fd = open(e_t->token->target[i], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		//perror(target[i]);
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		return (perror(""));
	}
	close(fd);
}

void	redir_outfile(t_env_token *e_t, int i)
{
	int	fd;

	fd = open(e_t->token->target[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		//perror(target[i]);
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		return (perror(""));
	}
	close(fd);
}

void	redir_heredoc(t_env_token *e_t, int i)
{
	if (dup2(e_t->token->hd_pipe[i][0], STDIN_FILENO) < 0)
	{
		return (perror(""));
	}
	close(e_t->token->hd_pipe[i][0]);
}

void	redirection(t_env_token *e_t)
{
	int	i;

	i = 0;
	while (e_t->token->redir[i] != NO_REDIR)
	{
		if (e_t->token->redir[i] == OUTFILE)
			redir_outfile(e_t, i);
		else if (e_t->token->redir[i] == APPEND)
			redir_append(e_t, i);
		else if (e_t->token->redir[i] == INFILE)
			redir_infile(e_t, i);
		else if (e_t->token->redir[i] == HEREDOC)
			redir_heredoc(e_t, i);
		i++;
	}
}
