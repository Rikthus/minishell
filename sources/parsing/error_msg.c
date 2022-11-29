/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:00:31 by tulipe            #+#    #+#             */
/*   Updated: 2022/11/29 19:23:22 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	err_minishell_usage(void)
{
	ft_putstr_fd("Usage: ./minishell\n", 2);
	return (0);
}

int	err_bad_envp_malloc(void)
{
	g_shell.exit_status = -1;
	ft_putstr_fd("Malloc failed\n", 2);
	return (1);
}

int	err_no_cmd(t_token *token, char *raw_line)
{
	free(raw_line);
	free_token(token);
	ft_putstr_fd("No command to exec\n", 2);
	g_shell.exit_status = 1;
	return (1);
}

int	perror_msg(int err)
{
	perror("");
	return (err);
}

int	error_malloc(int err)
{
	g_shell.exit_status = -1;
	ft_putstr_fd("Malloc failed\n", 2);
	return (err);
}
