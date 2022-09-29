/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:57:26 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/29 14:29:47 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//DONE
//NO VERIF
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
	if (str[i] == '=' && to_rm[i] == '\0')
		return (1);
	return (0);
}

static	void	remove_first_elem(t_envlist **env_list)
{
	t_envlist	*previous;
	t_envlist	*actual;

	previous = *env_list;
	actual = previous->next;
	free(previous->env_var);
	free(previous);
	*env_list = actual;
	return ;
}

static	void	env_remove(char *to_rm, t_envlist **env_list)
{
	t_envlist	*previous;
	t_envlist	*actual;
	t_envlist	*next;

	previous = *env_list;
	actual = previous->next;
	next = actual->next;
	if (is_var_to_remove(previous->env_var, to_rm))
		return (remove_first_elem(env_list));
	while (actual)
	{
		if (is_var_to_remove(actual->env_var, to_rm))
		{
			free(actual->env_var);
			free(actual);
			previous->next = next;
			return ;
		}
		if (!next)
			return;
		previous = previous->next;
		actual = actual->next;
		next = next->next;
	}
}

int	ft_unset(char **argv, t_envlist **env_list)
{
	int	i;

	i = 0;
	if (!(*env_list)->env_var)
		return (EXIT_FAILURE);
	while (argv[i])
		i++;
	if (i > 1)
	{
		if (argv[1][0] == '-')
			return (EXIT_FAILURE);
	}
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
	}
	return (EXIT_SUCCESS);
}
