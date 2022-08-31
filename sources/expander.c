/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:40:17 by tulipe            #+#    #+#             */
/*   Updated: 2022/08/31 18:41:16 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	*path_dup(char *start)
{
	
}

static	int	env_var_size(char *raw_line, int var_pos, char **envp)
{
	int		size;
	int		i;
	char	*path;

	size = 0;
	i = 0;
	path = path_dup(raw_line[var_pos]);
	if (!path)
		return (0);
	while (raw_line[i] && ft_isalnum(raw_line[i]))
	{
		
		i++;
	}	
	return (size);
}

void	expand_line(char *raw_line, char **expanded_line, char **envp)
{
	int	mono_quote;
	int	double_quote;
	int	i;

	mono_quote = 0;
	double_quote = 0;
	i = 0;
	while (raw_line[i])
	{
		
	}
}