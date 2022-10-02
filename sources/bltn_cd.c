/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 01:16:07 by tulipe            #+#    #+#             */
/*   Updated: 2022/10/03 01:13:07 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// not working for creating good pwd
static	int	update_env_list(char *new_pwd, char *old_pwd, t_envlist **env_list)
{
	char	**args;
	int		ret;

	args = malloc(sizeof(char *) * 4);
	if (!args)
	{
		free(new_pwd);
		free(old_pwd);
		return (-1);
	}
	args[0] = new_pwd;
	args[1] = new_pwd;
	args[2] = old_pwd;
	args[3] = NULL;
	ret = ft_export(args, env_list);
	free(new_pwd);
	free(old_pwd);
	free(args);
	return (ret);
}

static	int	change_env_vars(char *new_pwd, t_envlist **env_list)
{
	t_envlist	*tmp_env;
	char		*old_pwd;

	tmp_env = *env_list;
	old_pwd = NULL;
	if (!((*env_list)->env_var))
		(*env_list)->env_var = new_pwd;
	else
	{
		while (tmp_env && ft_strncmp(tmp_env->env_var, "PWD=", 4) != 0)
			tmp_env = tmp_env->next;
		if (tmp_env)
		{
			old_pwd = ft_strjoin("OLDPWD=", &(tmp_env->env_var[4]));
			if (!old_pwd)
			{
				free(new_pwd);
				return (-1);
			}
		}
		if (update_env_list(new_pwd, old_pwd, env_list) == -1)
			return (-1);
	}
	return (EXIT_SUCCESS);
}

static	char *ret_home_path(t_envlist *env_list)
{
	if (env_list->env_var)
	{
		while (env_list)
		{
			if (ft_strncmp(env_list->env_var, "HOME=", 5) == 0)
			{
				if (env_list->env_var[5] == '\0')
					return (NULL);
				return (&(env_list->env_var[5]));
			}
			env_list = env_list->next;
		}
	}
	ft_putstr_fd("Maxine ❤️: cd: HOME not set\n", 2);
	return (NULL);
}

static	int	move_dir(char *path, t_envlist **env_list)
{
	char	*new_pwd;
	
	if (chdir(path) == 0)
	{
		new_pwd = ft_strjoin("PWD=", path);
		if (!new_pwd || change_env_vars(new_pwd, env_list) == -1)
			return (-1);
	}
	else
	{
		ft_putstr_fd("Maxine ❤️: cd: ", 2);
		if (access(path, F_OK) == -1)
			ft_putstr_fd("no such file or directory: ", 2);
		else if (access(path, R_OK) == -1)
			ft_putstr_fd("permission denied: ", 2);
		else
			ft_putstr_fd("not a directory: ", 2);
		ft_putendl_fd(path, 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_cd(char **argv, t_envlist **env_list)
{
	int		i;
	char	*home_path;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
	{
		home_path = ret_home_path(*env_list);
		if (!home_path)
			return (EXIT_FAILURE);
		return (move_dir(home_path, env_list));
	}
	else if (i == 2)
		return(move_dir(argv[1], env_list));
	else
	{
		ft_putstr_fd("Maxine ❤️: cd: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}