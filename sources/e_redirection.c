/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:16:07 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/10/04 18:50:35 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	redir_infile(t_env_token *e_t, int i)
{
	int	fd;

	fd = open(e_t->token->target[i], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Maxine ❤️: ", 2);
		ft_putstr_fd(e_t->token->target[i], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		return (perror(""));
	close(fd);
}

static	void	redir_append(t_env_token *e_t, int i)
{
	int	fd;

	fd = open(e_t->token->target[i], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
		return (perror(""));
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (perror(""));
	close(fd);
}

static	void	redir_outfile(t_env_token *e_t, int i)
{
	int	fd;

	fd = open(e_t->token->target[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(""));
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (perror(""));
	close(fd);
}

static	void	redir_heredoc(t_env_token *e_t, int *nb_heredoc)
{
	if (dup2(e_t->token->hd_pipe[*nb_heredoc][0], STDIN_FILENO) < 0)
		return (perror(""));
	close(e_t->token->hd_pipe[*nb_heredoc][0]);
	*nb_heredoc += 1;
}

void	redirection(t_env_token *e_t)
{
	int	i;
	int	nb_heredoc;

	i = 0;
	nb_heredoc = 0;
	while (e_t->token->redir[i] != NO_REDIR)
	{
		if (e_t->token->redir[i] == OUTFILE)
			redir_outfile(e_t, i);
		else if (e_t->token->redir[i] == APPEND)
			redir_append(e_t, i);
		else if (e_t->token->redir[i] == INFILE)
			redir_infile(e_t, i);
		else if (e_t->token->redir[i] == HEREDOC)
			redir_heredoc(e_t, &nb_heredoc);
		i++;
	}
}
