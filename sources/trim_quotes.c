/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:02:06 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/23 20:49:56 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	trimmed_len(char *str)
{
	int		i;
	t_state	state;

	i = 0;
	state.sq = OFF;
	state.dq = OFF;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!change_quote_state(str[i], &state))
				i++;
		}
		else
			i++;
	}
	return (i);
}

static	void	cpy_trimmed(char **trimmed_str, char *str)
{
	int		i;
	int		j;
	t_state	state;

	i = 0;
	j = 0;
	state.sq = OFF;
	state.dq = OFF;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!change_quote_state(str[i], &state))
				*trimmed_str[j++] = str[i++];
			else
				i++;
		}
		else
			*trimmed_str[j++] = str[i++];
	}
	*trimmed_str[j] = '\0';
}

int	trim_quotes(char **str)
{
	int		t_len;
	char	*trimmed_str;

	t_len = trimmed_len(*str);
	if (t_len == ft_strlen(*str))
		return (1);
	trimmed_str = malloc(sizeof() * (t_len + 1));
	if (!trimmed_str)
		return (0);
	cpy_trimmed(&trimmed_str, *str);
	free(*str);
	*str = trimmed_str;
	return (1); 
}