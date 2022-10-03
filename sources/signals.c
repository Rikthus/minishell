/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:54:14 by tulipe            #+#    #+#             */
/*   Updated: 2022/10/03 02:57:36 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	handle_shell(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static	void	handle_exec(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", 1);
	else
		ft_putstr_fd("Quit: 3\n", 1);
}

static	void	handle_pstop(int signum)
{
	(void)signum;
	g_herestop = 1;
}

static	void	handle_heredoc(int signum)
{
	(void)signum;
	g_herestop = 1;
	close(0);
	ft_putstr_fd("\n", 1);
}

void	signal_mini(int	type)
{
	if (type == BASIC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_shell);
	}
	else if (type == PARENT_STOP)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_pstop);
	}
	else if (type == EXEC)
	{
		signal(SIGQUIT, handle_exec);
		signal(SIGINT, handle_exec);
	}
	else if (type == HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_heredoc);
	}
}
