/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:08:57 by tulipe            #+#    #+#             */
/*   Updated: 2022/11/29 19:24:36 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd_part_len(int *i, char *cmd, int type)
{
	int		len;
	t_state	state;

	len = *i;
	state.sq = OFF;
	state.dq = OFF;
	if (type == REDIR)
	{
		while (cmd[len] == '<' || cmd[len] == '>')
			len++;
	}
	else
	{
		while (cmd[len] && ((!ft_isspace(cmd[len]) && cmd[len] != '<'
					&& cmd[len] != '>') || (state.sq == ON || state.dq == ON)))
		{
			if (cmd[len] == '\'' || cmd[len] == '\"')
				change_quote_state(cmd[len], &state);
			len++;
		}
	}
	return (len - *i);
}

int	free_rd_line(char *line, int ret)
{
	free(line);
	return (ret);
}

int	change_quote_state(char quote, t_state *state)
{
	if (quote == '\'' && state->dq == OFF)
	{
		if (state->sq == OFF)
			state->sq = ON;
		else
			state->sq = OFF;
		return (CHANGED);
	}
	else if (quote == '\"' && state->sq == OFF)
	{
		if (state->dq == OFF)
			state->dq = ON;
		else
			state->dq = OFF;
		return (CHANGED);
	}
	return (0);
}

char	*custom_strdup(char *str, int start, int end)
{
	char	*dup;
	int		i;

	dup = malloc(sizeof(char) * ((end - start) + 2));
	if (!dup)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		dup[i] = str[start];
		start++;
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	is_line_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
