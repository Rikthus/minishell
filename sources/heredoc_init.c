/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:48:36 by maxperei          #+#    #+#             */
/*   Updated: 2022/09/29 18:17:36 by cdutel-l         ###   ########.fr       */
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

static	int	read_heredoc(int fd, char *eof)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line)
			return (0); // ERR
		if (line[0] != '\0' && ft_strcmp(line, eof) == 0)
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
	token->hd_pipe[pipe_i] = fd;
	if (pipe(fd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		if (!read_heredoc(token->hd_pipe[pipe_i][1], eof))
			exit(EXIT_FAILURE);
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	wait(NULL);
	return (1);
}

int	heredoc_init(t_token *token)
{
	int		i;

	while (token)
	{
		i = 0;
		while (token->redir[i] != NO_REDIR)
			i++;
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
			}
			i++;
		}
		token = token->next;
	}
	return (1);
}
