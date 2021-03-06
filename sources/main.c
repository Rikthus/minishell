/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:52:00 by maxperei          #+#    #+#             */
/*   Updated: 2022/06/03 19:12:50 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc > 1)
	{
		printf("Usage: ./minishell\n");
		return (g_status);
	}
	while (1)
	{
		if (shell(readline("choupishell <3 "), envp) == STOP_SHELL);
			break ;
	}
	return (g_status);
}
