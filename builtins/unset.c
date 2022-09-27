/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:57:26 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/27 01:15:04 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//test
int	is_valid_env(char *str)
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

int	main(int argc, char **argv)
{
	t_envlist	*previous;
	t_envlist	*actual;
	t_envlist	*follow;

	if (argc > 1)
	{
		if (argv[1][0] == '-' || !is_valid_env(argv[1]))
			return (1);
	}
	actual = g_mini.env_list;
	lst_removeif();
}