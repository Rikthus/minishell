/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:13:35 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/24 22:14:43 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	*dup_var_name(char *str, int i)
{
	char *dup_name;
	int	len;
	
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

static	void	dup_l_and_r(char *str, t_expan *exp)
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

int	init_exp(char **str, t_expan *exp)
{
	exp->left_dup = malloc(sizeof(char) * (exp->left_end + 1));
	if (!(exp->left_dup))
		return (0);
	exp->right_dup = malloc(sizeof(char) *
			(ft_strlen(str[0]) - 1 - exp->right_begin + 1));
	if (!(exp->right_dup))
	{
		free(exp->left_dup);
		return (0);
	}
	exp->var_name_dup = dup_var_name(str[0], exp->var_name_index);
	if (!exp->var_name_dup)
	{
		free(exp->left_dup);
		free(exp->right_dup);
		return (0);
	}
	dup_l_and_r(str[0], exp);
	exp->var_dup = NULL;
	return (1);
}

int	free_expan(t_expan *exp)
{
	free(exp->left_dup);
	free(exp->right_dup);
	free(exp->var_name_dup);
	free(exp->var_dup);
	return (0);
}

int	comp_var_name(char *env_var, char *dup_name)
{
	int	i;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
	{
		if (env_var[i] != dup_name[i])
			return (1);
		i++;
	}
	if (env_var[i] == '=' && dup_name[i] == '\0')
		return (0);
	else
		return (1);
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
		return (free_expan(exp));
	return (1);
}
