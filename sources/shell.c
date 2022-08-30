/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:09:25 by maxperei          #+#    #+#             */
/*   Updated: 2022/06/05 01:06:16 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	shell(char *line, char **envp)
{
	tokens = NULL;
	if (tokenizer(&tokens, line, envp) == BAD_SYNTAX)
	{
		free_tokens(tokens);
		return (RET_PROMPT);
	}
	return (RET_PROMPT);
}
