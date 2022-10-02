/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:12:04 by maxperei          #+#    #+#             */
/*   Updated: 2022/10/03 00:46:43 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	t_envlist	*add_env_elem(char *str)
{
	t_envlist	*new;

	new = malloc(sizeof(t_envlist));
	if (!new)
		return (NULL);
	new->next = NULL;
	if (!str)
	{
		new->env_var = NULL;
		return (new);
	}
	new->env_var = ft_strdup(str);
	if (!(new->env_var))
	{
		free(new);
		return (NULL);
	}
	return (new);
}

t_envlist	*make_env(char **envp)
{
	t_envlist	*env_list;
	t_envlist	*tmp;
	int			i;

	if (!envp[0])
		return (add_env_elem(NULL));
	env_list = add_env_elem(envp[0]);
	if (!env_list)
		return (NULL);
	tmp = env_list;
	i = 1;
	while (envp[i])
	{
		tmp->next = add_env_elem(envp[i]);
		if (!(tmp->next))
		{
			free_env(env_list);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	return (env_list);
}
