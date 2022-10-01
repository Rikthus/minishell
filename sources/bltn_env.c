/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:47:19 by tulipe            #+#    #+#             */
/*   Updated: 2022/10/01 23:04:19 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// DONE
// NO VERIF
int	ft_env(char **argv, t_envlist *env_list)
{
	int			i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 1)
	{
		ft_putstr_fd("env: no options handled\n", 2);
		return (EXIT_FAILURE);
	}
	while (env_list)
	{
		if (env_list->env_var)
		{
			ft_putstr_fd(env_list->env_var, 1);
			ft_putstr_fd("\n", 1);
		}
		env_list = env_list->next;
	}
	return (EXIT_SUCCESS);
}
