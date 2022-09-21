/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 01:09:44 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/21 20:07:56 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

//si $VAR vide
//si $VAR plein
//si $VAR ou "$VAR" ou '$VAR'
//si NESTED $VAR export lol="SUPER COOL $PATH okep"

#include "../includes/minishell.h"

static	int	is_exit_status(char *str)
{
	if (str[0] == '$' && str[1] == '?')
		return (1);
	return (0);
}

static	int	expand_target(t_token *token, int index)
{
	int		i;
	int		j;
	t_state	state;
	char	*path_dup;

	i = 0;
	state.sq = OFF;
	state.dq = OFF;
	while (token->target[index])
	{
		if (token->target[index][i] == '\'' || token->target[index][i] == '\"')
			change_quote_state(token->target[index][i], &state);
		if (state.sq == OFF && token->target[index][i] == '$'
				&& !is_exit_status(&(token->target[index][i])))
		{
			j = i + 1;
			while (ft_isalnum(token->target[index][j]))
				j++;
			path_dup = custom_dup(token->target[index], i + 1, j);
			if (!path_dup)
				return (0);
			if (!make_new_target_elem(token, index))
			{
				free(path_dup);
				return (0);
			}
			return (2);
		}
	}
	return (1);
}

static	int	expand_cmd(t_token *token, int index)
{
	int		i;
	int		j;
	t_state	state;
	char	*path_dup;

	i = 0;
	state.sq = OFF;
	state.dq = OFF;
	while (token->cmd[index][i])
	{
		if (token->cmd[index][i] == '\'' || token->cmd[index][i] == '\"')
			change_quote_state(token->cmd[index][i], &state);
		if (state.sq == OFF && token->cmd[index][i] == '$'
				&& !is_exit_status(&(token->cmd[index][i])))
		{
			j = i + 1;
			while (ft_isalnum(token->cmd[index][j]))
				j++;
			path_dup = custom_dup(token->cmd, i + 1, j);
			if (!path_dup)
				return (0);
			if (!make_new_cmd_elem(token,index, path_dup))
			{
				free(path_dup);
				return (0);
			}
			return (2);
		}
	}
	return (1);
}

int	expander(t_token **token, t_envlist *env_list)
{
	t_token	*tmp;
	int		i;
	int		expand_ret;

	tmp = *token;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			expand_ret = expand_cmd(tmp, i);
			if (expand_ret == 0)
				return (0);
			else if (expand_ret == 1)
				i++;
		}
		i = 0;
		while (tmp->target[i])
		{
			expand_ret = expand_target(tmp, i);
			if (expand_ret == 0)
				return (0);
			else if (expand_ret == 1)
				i++;
		}
		tmp = tmp->next;
	}
	return (1);
}