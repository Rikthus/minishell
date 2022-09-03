/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:52:07 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/04 01:38:57 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	check_char(char c)
{
	if (!ft_isalnum(c) && !ft_isspace(c) && c != '\'' && c != '\"' && c != '$'
		&& c != '<' && c != '>' && c != '|')
		return (0);
	return (1);	
}

static	int	check_too_many(char *redir)
{
	int		i;
	int		same_count;
	char	redir_char;

	i = 1;
	same_count = 0;
	redir_char = redir[0];
	while (redir[i] && i < 3)
	{
		if (redir[i] == redir_char)
			same_count++;
		i++;
	}
	if (same_count > 1)
		return (0);
	return (1);
}

static	int	is_redir(char *redir)
{
	int		i;
	int		valid_char;
	t_state	state;
	
	i = 1;
	valid_char = 0;
	state.sq = OFF;
	state.dq = OFF;
	if (!check_too_many(redir))
		return (0);
	while (redir[i] && !(redir[i] == '|' && state.sq == OFF && state.dq == OFF))
	{
		if (redir[i] == '\'' || redir[i] == '\"')
			change_quote_state(redir[i], &state);
		if (redir[i] != '<' && redir[i] != '>' && redir[i] != '\''
			&& redir[i] != '\"' && !ft_isspace(redir[i]))
			valid_char++;
		if ((state.sq == ON && redir[i] != '\'')
			|| (state.dq == ON && redir[i] != '\"'))
			valid_char++;
		i++;
	}
	if (valid_char == 0)
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