/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_find_absolute_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:25:13 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/11/29 19:26:22 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_absolute_path(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[0][i])
	{
		if (cmd[0][i] == '/')
			return (-1);
		i++;
	}
	return (0);
}
