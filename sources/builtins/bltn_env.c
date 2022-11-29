/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:47:19 by tulipe            #+#    #+#             */
/*   Updated: 2022/11/29 19:24:54 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	is_empty_var(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	ft_env(char **argv, t_envlist *env_list)
{
	int	i;

	i = 0;
	(void) argv;
	if (i > 1)
	{
		ft_putstr_fd("env: no options handled\n", 2);
		return (EXIT_FAILURE);
	}
	while (env_list)
	{
		if (env_list->env_var && is_empty_var(env_list->env_var) == 0)
		{
			ft_putstr_fd(env_list->env_var, 1);
			ft_putstr_fd("\n", 1);
		}
		env_list = env_list->next;
	}
	return (EXIT_SUCCESS);
}
