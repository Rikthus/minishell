/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 01:18:54 by tulipe            #+#    #+#             */
/*   Updated: 2022/11/29 19:24:01 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	free_redir_elem(t_elem *elems)
{
	while (elems)
	{
		if (elems->element[0] == '<' || elems->element[0] == '>')
			free(elems->element);
		elems = elems->next;
	}
}

static	t_token	*add_token(char *full_cmd)
{
	t_token	*token;
	t_elem	*elems;

	elems = break_cmd(full_cmd);
	if (!elems)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (free_elem(elems));
	token->cmd = NULL;
	token->redir = NULL;
	token->target = NULL;
	token->next = NULL;
	token->hd_pipe = NULL;
	if (fill_token(&token, elems) == 0)
	{
		free_token(token);
		return (free_elem(elems));
	}
	free_redir_elem(elems);
	free_elem_struct(elems);
	return (token);
}

t_token	*lexer(t_base *basic_token)
{
	t_token	*token;
	t_token	*tmp;

	token = add_token(basic_token->full_cmd);
	if (!token)
		return (NULL);
	basic_token = basic_token->next;
	tmp = token;
	while (basic_token)
	{
		tmp->next = add_token(basic_token->full_cmd);
		if (!(tmp->next))
			return (free_token(token));
		tmp = tmp->next;
		basic_token = basic_token->next;
	}
	return (token);
}
