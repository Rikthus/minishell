/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:17:45 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/16 14:40:33 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_elem_struct(t_elem *elems)
{
	t_elem	*previous;

	while (elems)
	{
		previous = elems;
		elems = elems->next;
		free(previous);
	}
}

void	free_basic_token(t_base *basic_token)
{
	t_base	*previous;

	while (basic_token)
	{
		previous = basic_token;
		basic_token = basic_token->next;
		free(previous->full_cmd);
		free(previous);
	}
}

void	*free_token(t_token *token)
{
	t_token	*previous;

	while (token)
	{
		previous = token;
		token = token->next;
		free_2d_array(previous->cmd);
		free(previous->redir);
		free_2d_array(previous->target);
		free(previous);
	}
	return (NULL);
}

void	*free_elem(t_elem *elems)
{
	t_elem	*previous;

	while (elems)
	{
		previous = elems;
		elems = elems->next;
		free(previous->element);
		free(previous);
	}
	return (NULL);
}