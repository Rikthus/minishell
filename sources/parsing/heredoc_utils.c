/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:31:51 by maxperei          #+#    #+#             */
/*   Updated: 2022/11/29 19:23:57 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_heredocs(t_token *token)
{
	int	i;
	int	nb_heredocs;

	i = 0;
	nb_heredocs = 0;
	while (token->redir[i] != NO_REDIR)
	{
		if (token->redir[i] == HEREDOC)
			nb_heredocs++;
		i++;
	}
	return (nb_heredocs);
}

int	forked_heredoc(t_token **token, char *eof, int pipe_i, int *fd)
{
	signal_mini(HEREDOC);
	if (!read_heredoc((*token)->hd_pipe[pipe_i][1], eof))
		return (EXIT_FAILURE);
	close(fd[0]);
	close(fd[1]);
	return (EXIT_SUCCESS);
}
