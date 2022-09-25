/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_find_absolute_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:25:13 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/09/18 15:08:38 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
