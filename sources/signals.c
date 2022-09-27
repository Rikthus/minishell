/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:54:14 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/27 21:16:48 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_shell(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		return ;
}

void	handle_exec(int signum)
{
	if (signum == SIGINT)
		printf("\n");
	else
		return ;
}

void	signal_exec(void)
{
	signal(SIGQUIT, handle_exec);
	signal(SIGINT, handle_exec);
}

void	signal_mini(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_shell);
}
