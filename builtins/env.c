/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:47:19 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/27 00:54:27 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv)
{
	t_envlist	*tmp_envlist;
	
	if (argc > 1)
		return (1);
	tmp_envlist = g_mini.env_list;
	while (tmp_envlist)
	{
		printf("%s\n", tmp_envlist->env_var);
		tmp_envlist = tmp_envlist->next;
	}
	return (0);
}