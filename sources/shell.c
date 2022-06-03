/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:09:25 by maxperei          #+#    #+#             */
/*   Updated: 2022/06/03 19:27:45 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	shell(char *line, char **envp)
{
	t_token	*tokens;

	tokens = NULL;
	if (tokenizer(&tokens, line, envp) == BAD_SYNTAX)
	{
		free_tokens(tokens);
		return (RET_PROMPT);
	}
	return (RET_PROMPT);
}
