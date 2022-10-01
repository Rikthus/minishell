/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:35:04 by tulipe            #+#    #+#             */
/*   Updated: 2022/10/01 23:01:37 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//DONE
//VERIFIED
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
	if (i > 1 || argv[1][0] == '-')
	{
		ft_putstr_fd("pwd: no options handled\n", 2);
		return (EXIT_FAILURE);
	}
	cwd = ft_getcwd(env_list);
	if (!cwd)
		return (0);
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
