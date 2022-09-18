/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 01:09:44 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/18 14:57:51 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

//si $VAR vide
//si $VAR plein
//si $VAR ou "$VAR" ou '$VAR'
//si NESTED $VAR export lol="SUPER COOL $PATH okep"

#include "../includes/minishell.h"

static	int	check_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

static	int	expander(t_token *tmp, int i, char **envp, int type)
{
	int	is_var;

	is_var = 0;
	while (is_var != -1)
	{
		if (type == CMD)
		{
			is_var = check_var(tmp->cmd[i]);
			if (is_var != -1)
				if (!expand())
					return (0);
		}
		else if (type == TARGET)
		{
			is_var = check_var(tmp->target[i]);
			if (is_var != -1)
				if (!expand())
					return (0);
		}
	}
	return (1);
}

void	*expansion(t_token **token, char **envp)
{
	t_token	*tmp;
	int		i;

	tmp = *token;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			if (tmp->cmd[i][0] != '\'')
			{
				if (!expander(tmp, i, envp, CMD))
					return (free_token(token));
			}
			i++;
		}
		i = 0;
		while (tmp->target[i])
		{
			if (tmp->target[i] != '\'')
			{
				if (!expander(tmp, i, envp, TARGET))
					return (free_token(token));
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (1);
}

