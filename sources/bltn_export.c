/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 01:16:26 by tulipe            #+#    #+#             */
/*   Updated: 2022/10/03 18:15:53 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	print_export(t_envlist *env_list)
{
	int	i;

	if (!env_list->env_var)
		return (EXIT_SUCCESS);
	while (env_list)
	{
		i = 0;
		ft_putstr_fd("declare -x ", 1);
		while (env_list->env_var[i] && env_list->env_var[i] != '=')
		{
			write(1, &(env_list->env_var[i]), 1);
			i++;
		}
		if (env_list->env_var[i] == '=')
		{
			i++;
			write(1, "=", 1);
			write(1, "\"", 1);
			ft_putstr_fd(&(env_list->env_var[i]), 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		env_list = env_list->next;
	}
	return (EXIT_SUCCESS);
}

static	int	is_valid_name(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
	{
		ft_putstr_fd("Maxine <3 : export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	while (str[i] && str[i] != '=')
	{
		if (str[i] && (ft_isalnum(str[i] || str[i] == '_')))
		{
			ft_putstr_fd("Maxine <3 : export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static	int	add_var_to_env(char *var, t_envlist **env_list)
{
	t_envlist	*tmp;
	t_envlist	*new;

	if (!(*env_list)->env_var)
	{
		(*env_list)->env_var = ft_strdup(var);
		if ((*env_list)->env_var)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	new = malloc(sizeof(t_envlist));
	if (!new)
		return (EXIT_FAILURE);
	new->env_var = ft_strdup(var);
	if (!(new->env_var))
	{
		free(new);
		return (EXIT_FAILURE);
	}
	new->next = NULL;
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (EXIT_SUCCESS);
}

static	char	**var_to_unset(char *full_var)
{
	int		i;
	char	*target;
	char	**big;

	i = 0;
	while (full_var[i] && full_var[i] != '=')
		i++;
	target = malloc(sizeof(char) * i);
	if (!target)
		return (NULL);
	i = 0;
	while (full_var[i] && full_var[i] != '=')
	{
		target[i] = full_var[i];
		i++;
	}
	target[i] = '\0';
	big = malloc(sizeof(char *) * 3);
	if (!big)
	{
		free(target);
		return (NULL);
	}
	big[0] = target;
	big[1] = target;
	big[2] = NULL;
	return (big);
}

int	ft_export(char **argv, t_envlist **env_list)
{
	int		i;
	char	**target_var;

	i = 1;
	if (argv[1] && argv[1][0] == '-')
	{
		ft_putstr_fd("export: no options handled\n", 2);
		return (EXIT_FAILURE);
	}
	else if (!argv[1])
		return (print_export(*env_list));
	while (argv[i])
	{
		if (is_valid_name(argv[i]) == 0)
		{
			target_var = var_to_unset(argv[i]);
			if (!target_var)
				return (-1);
			ft_unset(target_var, env_list);
			free(target_var[0]);
			free(target_var);
			if (!add_var_to_env(argv[i], env_list))
				return (-1);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
