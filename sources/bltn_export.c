/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 01:16:26 by tulipe            #+#    #+#             */
/*   Updated: 2022/10/02 16:52:33 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	print_export(t_envlist *env_list)
{
	int	i;

	if (!env_list->env_var)
		return (EXIT_SUCCESS);
	while(env_list)
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

int	ft_export(char **argv, t_envlist **env_list)
{
	int	i;

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
			ft_unset(&argv[i], env_list); // limite limite la technique.
			if (!add_var_to_env(argv[i], env_list))
				return (-1);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
