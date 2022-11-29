/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:02:06 by tulipe            #+#    #+#             */
/*   Updated: 2022/11/29 19:24:28 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	trimmed_len(char *str)
{
	int		i;
	int		len;
	t_state	state;

	i = 0;
	len = 0;
	state.sq = OFF;
	state.dq = OFF;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!change_quote_state(str[i], &state))
				len++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

static	void	cpy_trim_norm(char **trimmed_str, char *str, int *i, int *j)
{
	trimmed_str[0][*j] = str[*i];
	*j += 1;
	*i += 1;
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
			{
				trimmed_str[0][j] = str[i];
				i++;
				j++;
			}
			else
				i++;
		}
		else
			cpy_trim_norm(trimmed_str, str, &i, &j);
	}
	trimmed_str[0][j] = '\0';
}

int	trim_quotes(char **str)
{
	size_t	t_len;
	char	*trimmed_str;

	t_len = trimmed_len(*str);
	if (t_len == ft_strlen(*str))
		return (1);
	trimmed_str = malloc(sizeof(char) * (t_len + 1));
	if (!trimmed_str)
		return (0);
	cpy_trimmed(&trimmed_str, *str);
	free(*str);
	*str = trimmed_str;
	return (1);
}
