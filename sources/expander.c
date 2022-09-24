/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 01:09:44 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/24 22:19:55 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	full_len(t_expan exp)
{
	int	i;
	int	full_len;

	full_len = 0;
	i = 0;
	while (exp.left_dup[i])
		i++;
	full_len += i;
	i = 0;
	while (exp.right_dup[i])
		i++;
	full_len += i;
	if (exp.var_dup)
	{
		i = 0;
		while (exp.var_dup[i])
			i++;
		full_len += i;
	}
	return (full_len);
}

static	int	join_all(char **str, t_expan exp)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(sizeof(char) * (full_len(exp) + 1));
	if (!new_str)
		return (free_expan(&exp));
	i = 0;
	j = 0;
	while (exp.left_dup[i])
	{
		new_str[j] = exp.left_dup[i];
		i++;
		j++;
	}
	if (exp.var_dup)
	{
		i = 0;
		while (exp.var_dup[i])
		{
			new_str[j] = exp.var_dup[i];
			i++;
			j++;
		}
	}
	i = 0;
	while (exp.right_dup[i])
	{
		new_str[j] = exp.right_dup[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	free(str[0]);
	free_expan(&exp);
	str[0] = new_str;
	return (1);
}

static	int	expand(char **str, t_envlist *env_list, t_expan exp)
{
	if (!init_exp(str, &exp))
		return (0);
	while(env_list)
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
		if (state.sq == OFF && str[0][i] == '$'  && str[0][i + 1] != '\0'
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