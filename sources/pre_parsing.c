/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:52:07 by tulipe            #+#    #+#             */
/*   Updated: 2022/08/31 18:44:17 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	check_char(char c)
{
	if (!ft_isalnum(c) && !ft_isspace(c) && c != '\'' && c != '\"' && c != '$' && c != '<'
		&& c != '>' && c != '|')
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
		i++;
	}
	if (state.sq == ON || state.dq == ON)
		return (0);
	return (1);
}