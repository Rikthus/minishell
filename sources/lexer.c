/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 01:18:54 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/10 17:20:44 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	t_token	*add_token(char *full_cmd)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->redir = NULL;
	new->target = NULL;
	new->next = NULL;
	fill_new(&new, full_cmd);
	if (!(new->cmd) && !(new->redir))
		return (NULL);
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
	return (new);
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
