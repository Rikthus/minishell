/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:48:55 by tulipe            #+#    #+#             */
/*   Updated: 2022/11/29 19:24:08 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	part_len(char *str)
{
	t_state	state;
	int		i;

	state.sq = OFF;
	state.dq = OFF;
	i = 0;
	while (str[i] && !(str[i] == '|' && state.sq == OFF && state.dq == OFF))
	{
		if (str[i] == '\'' || str[i] == '\"')
			change_quote_state(str[i], &state);
		i++;
	}
	return (i);
}

static	int	part_counter(char *str)
{
	t_state	state;
	int		nb_parts;
	int		i;

	state.sq = OFF;
	state.dq = OFF;
	nb_parts = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			change_quote_state(str[i], &state);
		if (str[i] == '|' && state.sq == OFF && state.dq == OFF)
			nb_parts++;
		i++;
	}
	return (nb_parts);
}

static	char	*part_dup(char *str)
{
	t_state	state;
	int		i;
	char	*dup;

	state.sq = OFF;
	state.dq = OFF;
	i = 0;
	if (!str)
		return (NULL);
	dup = malloc(sizeof(char) * (part_len(str) + 1));
	if (!dup)
		return (NULL);
	while (str[i] && !(str[i] == '|' && state.sq == OFF && state.dq == OFF))
	{
		if (str[i] == '\'' || str[i] == '\"')
			change_quote_state(str[i], &state);
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static	int	find_next_part(char *str)
{
	t_state	state;
	int		j;

	state.sq = OFF;
	state.dq = OFF;
	j = 0;
	while (str[j] && !(str[j] == '|' && state.sq == OFF && state.dq == OFF))
	{
		if (str[j] == '\'' || str[j] == '\"')
			change_quote_state(str[j], &state);
		j++;
	}
	if (str[j] == '|')
		j++;
	return (j);
}

char	**pipe_split(char *str)
{
	int		i;
	int		j;
	int		nb_parts;
	char	**split;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	nb_parts = part_counter(str);
	split = malloc(sizeof(*split) * (nb_parts + 1));
	if (!split)
		return (0);
	while (str[j])
	{
		split[i] = part_dup(&str[j]);
		if (!split[i])
			return (free_split_error(split, i - 1));
		j += find_next_part(&str[j]);
		i++;
	}
	split[i] = NULL;
	return (split);
}
