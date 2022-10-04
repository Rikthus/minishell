/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:48:36 by maxperei          #+#    #+#             */
/*   Updated: 2022/10/04 19:03:24 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	malloc_heredocs(t_token *token)
{
	int		nb_heredoc;
	int		i;

	nb_heredoc = 0;
	i = 0;
	while (token->redir[i] != NO_REDIR)
	{
		if (token->redir[i] == HEREDOC)
			nb_heredoc++;
		i++;
	}
	token->hd_pipe = malloc(sizeof(int *) * nb_heredoc);
	if (!token->hd_pipe)
		return (0);
	return (1);
}

int	read_heredoc(int fd, char *eof)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if ((line[0] != '\0' && ft_strcmp(line, eof) == 0)
			|| g_shell.herestop == 1)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (1);
}

static	int	add_heredoc(t_token *token, int pipe_i, char *eof)
{
	int		*fd;
	pid_t	pid;

	fd = malloc(sizeof(int) * 2);
	if (!fd)
		return (error_malloc(0));
	token->hd_pipe[pipe_i] = fd;
	if (pipe(fd) == -1)
		return (perror_msg(0));
	signal_mini(PARENT_STOP);
	pid = fork();
	if (pid == -1)
		return (perror_msg(0));
	if (pid == 0)
		exit(forked_heredoc(&token, eof, pipe_i, fd));
	close(fd[1]);
	wait(NULL);
	signal_mini(BASIC);
	return (1);
}

int	heredoc_init(t_token *token)
{
	int		i;

	while (token)
	{
		i = count_heredocs(token);
		if (i > 0)
		{
			if (!malloc_heredocs(token))
				return (0);
		}
		i = 0;
		while (token->redir[i] != NO_REDIR)
		{
			if (token->redir[i] == HEREDOC)
			{
				if (!add_heredoc(token, i, token->target[i]))
					return (0);
				if (g_shell.herestop == 1)
					return (1);
			}
			i++;
		}
		token = token->next;
	}
	return (1);
}
