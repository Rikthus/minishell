/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:48:36 by maxperei          #+#    #+#             */
/*   Updated: 2022/09/29 13:10:22 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	count_heredocs(t_token *token)
{
	int		nb_heredoc;
	int		i;

	nb_heredoc = 0;
	while (token)
	{
		i = 0;
		while (token->redir[i] != NO_REDIR)
		{
			if (token->redir[i] == HEREDOC)
				nb_heredoc++;
		}
		token = token->next;
	}
	return (nb_heredoc);
}

static	int	add_heredoc(t_token *token)
{
	int		*fd;
	pid_t	pid;

	fd = malloc(sizeof(int *) * 2);
	if (!fd)
		return (0);
	token->hd_pipe = fd;
	if (pipe(fd) == -1)
		return (0);
		pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		
	}
	wait(NULL);
	return (1);
}

/**
 * @brief test explaination for function
 *
 * @param token
 * @return int
 */
int	heredoc_init(t_token *token)
{
	int		nb_heredoc;
	t_token	*tmp_token;

	nb_heredoc = count_heredocs(token);
	if (nb_heredoc == 0)
		return (1);
	while (token)
	{
		if (!add_heredoc(token))
			return (0);
		token = token->next;
	}
	return (1);
}
