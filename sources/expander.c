/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 01:09:44 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/26 16:32:12 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	join_all(char **str, t_expan exp)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * (full_line_len(exp) + 1));
	if (!new_str)
		return (free_expan(&exp));
	cpy_full_line(exp, &new_str);
	free(str[0]);
	free_expan(&exp);
	str[0] = new_str;
	return (1);
}

static	int	expand(char **str, t_envlist *env_list, t_expan exp)
{
	if (!init_exp(str, &exp))
		return (0);
	while (env_list)
	{
		if (comp_var_name(env_list->env_var, exp.var_name_dup) == 0)
		{
			if (!dup_var(env_list->env_var, &exp))
				return (0);
			break ;
		}
		env_list = env_list->next;
	}
	if (!join_all(str, exp))
		return (0);
	return (1);
}

static	int	find_env_var(char **str, t_envlist *env_list)
{
	t_expan	exp;
	t_state	state;
	int		i;

	state.sq = OFF;
	state.dq = OFF;
	i = 0;
	while (str[0][i])
	{
		if (str[0][i] == '\'' || str[0][i] == '\"')
			change_quote_state(str[0][i], &state);
		if (state.sq == OFF && str[0][i] == '$' && str[0][i + 1] != '\0'
				&& str[0][i + 1] != '?')
		{
			exp.left_end = i;
			exp.var_name_index = i + 1;
			i++;
			while (str[0][i] && ft_isalnum(str[0][i]))
				i++;
			exp.right_begin = i;
			if (!expand(str, env_list, exp))
				return (0);
		}
		i++;
	}
	if (!trim_quotes(str))
		return (0);
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
			if (!find_env_var(&(tmp->cmd[i]), env_list))
				return (0);
			i++;
		}
		i = 0;
		while (tmp->target[i])
		{
			if (!find_env_var(&(tmp->target[i]), env_list))
				return (0);
			i++;
		}
		tmp = tmp->next;
	}
	return (1);
}
