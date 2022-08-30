/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:19:07 by maxperei          #+#    #+#             */
/*   Updated: 2022/06/05 01:01:54 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_token(t_pre_token **tokens, char *start, int end, char **envp)
{
	t_pre_token	*new_tok;

	new_tok= *tokens;
	while (new_tok->next)
		new_tok = new_tok->next;
	new_tok->ft_strdup_end()

}

int	tokenizer(t_pre_token **tokens, char *line, char **envp)
{

}
