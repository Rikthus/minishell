/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:54:14 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/30 02:47:49 by tulipe           ###   ########lyon.fr   */
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
}

void	handle_exec(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", 1);
	else
		ft_putstr_fd("Quit: 3\n", 1);
}

void	handle_heredoc(int signum)
{
	(void)signum;
	g_herestop = 1;
	write(1, "OK", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ft_putstr_fd("\n", 1);
}

void	signal_exec(void)
{
	signal(SIGQUIT, handle_exec);
	signal(SIGINT, handle_exec);
}

void	signal_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_heredoc);
}

void	signal_mini(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_shell);
}
