/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:04:20 by maxperei          #+#    #+#             */
/*   Updated: 2022/11/29 19:24:43 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	init_args(char ***args, char *full_newpwd, char *old_pwd)
{
	args[0][0] = full_newpwd;
	args[0][1] = full_newpwd;
	args[0][2] = old_pwd;
	args[0][3] = NULL;
}

int	update_env_list(char *new_pwd, char *old_pwd, t_envlist **env_list)
{
	char	**args;
	char	*full_newpwd;
	int		ret;

	full_newpwd = ft_strjoin("PWD=", new_pwd);
	free(new_pwd);
	if (!full_newpwd)
	{
		free(old_pwd);
		return (-1);
	}
	args = malloc(sizeof(char *) * 4);
	if (!args)
	{
		free(full_newpwd);
		free(old_pwd);
		return (-1);
	}
	init_args(&args, full_newpwd, old_pwd);
	ret = ft_export(args, env_list);
	free(full_newpwd);
	free(old_pwd);
	free(args);
	return (ret);
}
