/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:47:19 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/30 15:02:40 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ADD CHECK NO = env var

// DONE
// NO VERIF
int	ft_env(char **argv, t_envlist *env_list)
{
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
