/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:19:07 by maxperei          #+#    #+#             */
/*   Updated: 2022/06/03 19:33:45 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_token(t_tokens **tokens, char *start, int end, char **envp)
{
	t_tokens	*new_tok;

	new_tok= *tokens;
	while (new_tok->next)
		new_tok = new_tok->next;
	new_tok->ft_strdup_end()

}

int	tokenizer(t_tokens **tokens, char *line, char **envp)
{

}
