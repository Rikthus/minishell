/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_builtin_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:16:07 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/11/29 19:26:13 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	redir_infile(t_env_token *e_t, int i)
{
	int	fd;

	fd = open(e_t->token->target[i], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Maxine ❤️: ", 2);
		ft_putstr_fd(e_t->token->target[i], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_shell.exit_status = 1;
		return (-1);
	}
	close(fd);
	return (0);
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

int	built_redirection(t_env_token *e_t)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (e_t->token->redir[i] != NO_REDIR)
	{
		if (e_t->token->redir[i] == OUTFILE)
			redir_outfile(e_t, i);
		else if (e_t->token->redir[i] == APPEND)
			redir_append(e_t, i);
		else if (e_t->token->redir[i] == INFILE)
			ret = redir_infile(e_t, i);
		i++;
	}
	return (ret);
}
