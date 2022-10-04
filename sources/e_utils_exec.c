/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:51:25 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/10/04 20:44:03 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	return (envp[i]);
}

int	find_size_env(t_envlist *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**custom_envp(t_envlist *envp)
{
	t_envlist	*env;
	char		**tab_envp;
	int			i;

	env = envp;
	i = find_size_env(env);
	tab_envp = malloc(sizeof(char *) * (i + 1));
	if (!tab_envp)
		return (NULL);
	i = 0;
	env = envp;
	while (env)
	{
		tab_envp[i] = ft_strdup(env->env_var);
		if (!tab_envp[i])
		{
			free_2d_array(tab_envp);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	tab_envp[i] = NULL;
	return (tab_envp);
}

char	*exec_cmd(char	**cmds, char *env_path)
{
	char	**tab_paths;
	char	*a_path;
	char	*good_path;
	int		i;

	i = 0;
	good_path = NULL;
	tab_paths = ft_split_mod(env_path, ':');
	while (tab_paths[i])
	{
		a_path = ft_strjoin_mini(tab_paths[i], cmds[0]);
		if (access(a_path, X_OK) == 0)
			good_path = a_path;
		i++;
	}
	if (!good_path)
	{
		ft_putstr_fd("Maxine ❤️: ", 2);
		ft_putstr_fd(cmds[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (good_path);
}

char	*prepare_commands(t_token *token, t_envlist *envp)
{
	char		*good_path;
	char		*envp_path;
	char		**tab_env;

	good_path = NULL;
	tab_env = custom_envp(envp);
	envp_path = env_path(tab_env);
	if (!envp_path)
	{
		ft_putstr_fd("Maxine ❤️: ", 2);
		ft_putstr_fd(token->cmd[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (NULL);
	}
	if (find_absolute_path(token->cmd) == -1)
		good_path = token->cmd[0];
	else if (find_absolute_path(token->cmd) == 0)
		good_path = exec_cmd(token->cmd, envp_path);
	return (good_path);
}
