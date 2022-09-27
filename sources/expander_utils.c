/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:13:35 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/27 17:52:47 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_exp(char **str, t_expan *exp)
{
	exp->left_dup = malloc(sizeof(char) * (exp->left_end + 1));
	if (!(exp->left_dup))
		return (0);
	exp->right_dup = malloc(sizeof(char)
			* (ft_strlen(str[0]) - 1 - exp->right_begin + 1));
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
	cpy_l_and_r(str[0], exp);
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

int	full_line_len(t_expan exp)
{
	int	i;
	int	full_len;

	full_len = 0;
	i = 0;
	while (exp.left_dup[i])
		i++;
	full_len += i;
	i = 0;
	while (exp.right_dup[i])
		i++;
	full_len += i;
	if (exp.var_dup)
	{
		i = 0;
		while (exp.var_dup[i])
			i++;
		full_len += i;
	}
	return (full_len);
}
