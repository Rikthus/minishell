/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:47:19 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/28 17:38:28 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// DONE
// NO VERIF
int	env(char **argv, t_envlist *env_list)
{
	t_envlist	*tmp_envlist;
	int			i;
	
	i = 0;
	while (argv[i])
		i++;
	if (i > 1)
		return (EXIT_FAILURE);
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