/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dups.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:26:02 by maxperei          #+#    #+#             */
/*   Updated: 2022/11/29 19:23:26 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*dup_var_name(char *str, int i)
{
	char	*dup_name;
	int		len;

	len = i;
	while (str[len] && ft_isalnum(str[len]))
		len++;
	dup_name = malloc(sizeof(char) * (len - i + 1));
	if (!dup_name)
		return (NULL);
	len = 0;
	while (str[i] && ft_isalnum(str[i]))
	{
		dup_name[len] = str[i];
		len++;
		i++;
	}
	dup_name[len] = '\0';
	return (dup_name);
}

void	cpy_l_and_r(char *str, t_expan *exp)
{
	int	i;
	int	j;

	i = 0;
	while (i < exp->left_end)
	{
		exp->left_dup[i] = str[i];
		i++;
	}
	exp->left_dup[i] = '\0';
	i = 0;
	j = exp->right_begin;
	while (str[j])
	{
		exp->right_dup[i] = str[j];
		i++;
		j++;
	}
	exp->right_dup[i] = '\0';
}

int	dup_var(char *env_var, t_expan *exp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_var[j] && env_var[j] != '=')
		j++;
	if (env_var[j] == '\0')
		return (0);
	*(exp->cmd_index) = *(exp->cmd_index) + ft_strlen(&env_var[j + 1]);
	exp->var_dup = malloc(sizeof(char) * (ft_strlen(&env_var[j + 1]) + 1));
	if (!exp->var_dup)
		return (free_expan(exp));
	j++;
	while (env_var[j])
	{
		exp->var_dup[i] = env_var[j];
		i++;
		j++;
	}
	exp->var_dup[i] = '\0';
	if (!trim_quotes(&(exp->var_dup)))
		return (0);
	return (1);
}

static	void	cpy_var_dup(t_expan exp, int *j, char **new_line)
{
	int	i;

	i = 0;
	while (exp.var_dup[i])
	{
		new_line[0][*j] = exp.var_dup[i];
		i++;
		*j += 1;
	}
}

void	cpy_full_line(t_expan exp, char **new_line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (exp.left_dup[i])
	{
		new_line[0][j] = exp.left_dup[i];
		i++;
		j++;
	}
	if (exp.var_dup)
		cpy_var_dup(exp, &j, new_line);
	i = 0;
	while (exp.right_dup[i])
	{
		new_line[0][j] = exp.right_dup[i];
		i++;
		j++;
	}
	new_line[0][j] = '\0';
}
