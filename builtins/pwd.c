/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:35:04 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/29 14:29:42 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//DONE
//NO VERIF
static	char	*ft_getcwd(t_envlist *env_list)
{
	char	*cwd;

	cwd = NULL;
	while (env_list)
	{
		if (ft_strncmp(env_list->env_var, "PWD=", 4) == 0)
		{
			cwd = ft_strdup(&(env_list->env_var[5]));
			if (!cwd)
				return (NULL);
			return (cwd);
		}
		env_list = env_list->next;
	}
	return (cwd);
}

int	ft_pwd(char **argv, t_envlist *env_list)
{
	char	*cwd;
	int		i;

	i = 0;
	if (!(env_list->env_var))
		return (1);
	while (argv[i])
		i++;
	if (i > 1)
	{
		if (argv[1][0] == '-')
			return (EXIT_FAILURE);
	}
	cwd = ft_getcwd(env_list);
	if (!cwd)
		return (0);
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
