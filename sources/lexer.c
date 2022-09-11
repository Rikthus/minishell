/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 01:18:54 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/11 15:55:13 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	print_elems(t_elem *elems)
{
	while (elems)
	{
		printf("%s\n", elems->element);
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
	print_elems(elems);
	token = NULL;
	// token = malloc(sizeof(t_token));
	// if (!token)
	// 	return (NULL);
	// token->cmd = NULL;
	// token->redir = NULL;
	// token->target = NULL;
	// token->next = NULL;
	// fill_new(&token, elems);
	// if (!(token->cmd) && !(token->redir))
	// 	return (NULL);
	// new->redir = find_redir(full_cmd);
	// if (!(new->redir))
	// 	return (free_token(new));
	// if ((new->redir)[0] == NO_REDIR)
	// {
	// 	new->target = find_target(full_cmd, new->redir);
	// 	if (!(new->target))
	// 		return (free_token(new));
	// }
	// new->cmd = find_cmd(full_cmd);
	// if (!(new->cmd))
	// 	return (free_token(new));
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
		if (!(tmp->cmd))
			return (free_token(token));
		tmp = tmp->next;
		basic_token = basic_token->next;
	}
	return (token);
}
