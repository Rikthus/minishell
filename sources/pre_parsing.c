/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:52:07 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/28 10:59:10 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_tokens(t_token *token)
{
	while (token)
	{
		if (!(token->cmd[0]))
			return (0);
		token = token->next;
	}
	return (1);
}

static	int	check_char(char c)
{
	if (!ft_isalnum(c) && !ft_isspace(c) && c != '-' && c != '\'' && c != '\"'
		&& c != '$' && c != '<' && c != '>' && c != '|' && c != '/'
		&& c != '=' && c != '.')
		return (0);
	return (1);
}

static	int	check_pipe(char *redir)
{
	int	i;
	
	i = 1;
	if (redir[i] == '|')
		return (0);
	while (redir[i] && ft_isspace(redir[i]))
		i++;
	if (!redir[i] || redir[i] == '|')
		return (0);
	return (1);
}

static	int	is_redir(char *redir)
{
	int		i;
	char	redir_char;

	redir_char = redir[0];
	i = 1;
	if (redir_char == '|')
	{
		if (!check_pipe(redir))
			return (0);
	}
	else if (redir_char == '<' || redir_char == '>')
	{
		if ((redir_char == '<' && redir[i] == '>')
			|| (redir_char == '>' && redir[i] == '<'))
			return (0);
	}
	if (redir[i] && redir[i] != redir_char && redir[i] != '|'
		&& !ft_isspace(redir[i] && redir[i]))
		return (1);
	i++;
	while (redir[i] && ft_isspace(redir[i]))
		i++;
	if (!redir[i] || redir[i] == '|'
		|| redir[i] == '<' || redir[i] == '>')
		return (0);
	return (1);
}

int	pre_parsing(char *raw_line)
{
	t_state	state;
	int		i;

	state.sq = OFF;
	state.dq = OFF;
	i = 0;
	while (raw_line[i] && ft_isspace(raw_line[i]))
		i++;
	if (raw_line[i] == '|')
		return (0);
	while (raw_line[i])
	{
		if (raw_line[i] == '\'' || raw_line[i] == '\"')
			change_quote_state(raw_line[i], &state);
		if (state.sq == OFF && state.dq == OFF && !check_char(raw_line[i]))
			return (0);
		if (state.sq == OFF && state.dq == OFF && (raw_line[i] == '|'
				|| raw_line[i] == '<' || raw_line[i] == '>')
			&& !is_redir(&raw_line[i]))
			return (0);
		i++;
	}
	if (state.sq == ON || state.dq == ON)
		return (0);
	return (1);
}
