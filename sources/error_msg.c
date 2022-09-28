/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:00:31 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/28 11:01:13 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	err_minishell_usage(void)
{
	printf("Usage: ./minishell\n");
	return (0);
}

int	err_bad_envp_malloc(void)
{
	printf("Malloc failed\n");
	return (1);
}

int	err_no_cmd(t_token *token, char *raw_line)
{
	free(raw_line);
	free_token(token);
	printf("No command to exec\n");
	return (1);
}