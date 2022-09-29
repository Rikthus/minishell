/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:17:45 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/29 16:42:58 by cdutel-l         ###   ########.fr       */
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
	int		i;
	int		nb_heredoc;

	while (token)
	{
		previous = token;
		token = token->next;
		i = 0;
		nb_heredoc = 0;
		while (previous->redir[i] != NO_REDIR)
		{
			if (previous->redir[i] == HEREDOC)
				nb_heredoc++;
			i++;
		}
		if (nb_heredoc > 0)
			free_2d_int_array(previous->hd_pipe, nb_heredoc);
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

void	free_env(t_envlist *envlist)
{
	t_envlist	*previous;

	while (envlist)
	{
		previous = envlist;
		envlist = envlist->next;
		free(previous->env_var);
		free(previous);
	}
}
