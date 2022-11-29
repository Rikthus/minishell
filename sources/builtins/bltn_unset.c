/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:57:26 by tulipe            #+#    #+#             */
/*   Updated: 2022/11/29 19:25:09 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	is_valid_env_name(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static	int	is_var_to_remove(char *str, char *to_rm)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] != to_rm[i])
			return (0);
		i++;
	}
	if ((str[i] == '\0' || str[i] == '=') && to_rm[i] == '\0')
		return (1);
	return (0);
}

static	void	remove_first_elem(t_envlist **env_list)
{
	t_envlist	*actual;

	actual = *env_list;
	if (!actual->next)
	{
		free(actual->env_var);
		return ;
	}
	*env_list = actual->next;
	free(actual->env_var);
	free(actual);
	return ;
}

static	void	env_remove(char *to_rm, t_envlist **env_list)
{
	t_envlist	*previous;
	t_envlist	*actual;

	previous = *env_list;
	actual = previous->next;
	if (is_var_to_remove(previous->env_var, to_rm))
		return (remove_first_elem(env_list));
	while (actual)
	{
		if (is_var_to_remove(actual->env_var, to_rm))
		{
			previous->next = actual->next;
			free(actual->env_var);
			free(actual);
			return ;
		}
		previous = previous->next;
		actual = actual->next;
	}
}

int	ft_unset(char **argv, t_envlist **env_list)
{
	int	i;

	if (!(*env_list)->env_var)
		return (EXIT_SUCCESS);
	i = 1;
	while (argv[i])
	{
		if (is_valid_env_name(argv[i]))
			env_remove(argv[i], env_list);
		else
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid indentifier\n", 2);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
