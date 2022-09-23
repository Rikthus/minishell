/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 01:09:44 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/23 19:37:15 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	no_envvar(char *str)
{
	int		i;
	t_state	state;

	i = 0;
	state.sq = OFF;
	state.dq = OFF;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			change_quote_state(str[i], &state);
		if (state.sq == OFF && str[i] == '$' && str[i + 1] != '\0'
				&& !is_exit_status(&str[i]))
			return (0);
		i++;
	}
	return (1);
}

static	int	expand(char **str, t_expan *exp)
{
	if (no_envvar(exp->var_dup))
		if (!join_all(str, exp))
			return (0);
	
}

static	t_expan	*init_expan(void)
{
	t_expan	*exp;
	
	exp = malloc(sizeof(t_expan));
	if (!exp)
		return (NULL);
	exp->start_dup = NULL;
	exp->end_dup = NULL;
	exp->var_name_dup = NULL;
	exp->var_dup = NULL;
	return (exp);
}

static	int	expand_cmd(char **str)
{
	t_expan	*exp;
	t_state	state;
	int		i;

	exp = init_expan();
	if (!exp)
		return (0);
	state.sq = OFF;
	state.dq = OFF;
	while (*str[i])
	{
		if (*str[i] == '\'' || *str[i] == '\"')
			change_quote_state(*str[i], &state);
		if (state.sq == OFF && *str[i] == '$' && !is_exit_status(&(*str[i]))
				&& *str[i + 1] != '\0')
		{
			exp->end_begin = i;
			exp->var_name_index = i + 1;
			while (*str[i] && ft_isalnum(*str[i]))
				i++;
			exp->start_end = i;
			if (!expand(str, exp))
				return (free_expan(exp));
		}
		i++;
	}
	return (1);
}

int	expander(t_token **token, t_envlist *env_list)
{
	t_token	*tmp;
	int		i;

	tmp = *token;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			if (!expand_cmd(&(tmp->cmd[i])))
				return (0);
			i++;
		}
		//TARGET EXPANSION
		tmp = tmp->next;
	}
	return (1);
}