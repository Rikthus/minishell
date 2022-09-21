/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:08:57 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/21 17:48:56 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_part_len(int *i, char *cmd, int type)
{
	int		len;
	char	quote;

	len = *i;
	if (type == QUOTE)
	{
		quote = cmd[len];
		len++;
		while (cmd[len] != quote)
			len++;
		len++;
	}
	else if (type == REDIR)
	{
		while (cmd[len] == '<' || cmd[len] == '>')
			len++;
	}
	else
	{
		while (cmd[len] && !ft_isspace(cmd[len]) && cmd[len] != '\''
			&& cmd[len] != '\"' && cmd[len] != '<' && cmd[len] != '>')
			len++;
	}
	return (len - *i);
}

int	free_rd_line(char *line, int ret)
{
	free(line);
	return (ret);
}

void	change_quote_state(char quote, t_state *state)
{
	if (quote == '\'' && state->dq == OFF)
	{
		if (state->sq == OFF)
			state->sq = ON;
		else
			state->sq = OFF;
	}
	else if (quote == '\"' && state->sq == OFF)
	{
		if (state->dq == OFF)
			state->dq = ON;
		else
			state->dq = OFF;
	}
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
