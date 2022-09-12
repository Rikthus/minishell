/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 01:18:54 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/11 23:04:10 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static	int	nb_elem(t_elem *elems, int type)
{
	int	nb;

	nb = 0;
	if (type == REDIR)
	{
		while (elems)
		{
			if (elems->element[0] == '<' || elems->element[0] == '>')
				nb++;
			elems = elems->next;
		}
	}
	else if (type == WORD)
	{
		while (elems)
		{
			if (elems->element[0] == '<' || elems->element[0] == '>')
				nb--;
			else
				nb++;
			elems = elems->next;
		}
	}
	return (nb);
}

static	int	token_malloc(t_token **token, t_elem *elems, t_index *i)
{
	(*token)->target = malloc(sizeof(POINTER) * (nb_elem(elems, REDIR) + 1));
	if (!((*token)->target))
		return (0);
	(*token)->redir = malloc(sizeof(int) * (nb_elem(elems, REDIR) + 1));
	if (!((*token)->redir))
		return (0);
	(*token)->cmd = malloc(sizeof(POINTER) * (nb_elem(elems, WORD) + 1));
	if (!((*token)->cmd))
		return (0);
	i->cmd_i = 0;
	i->redir_i = 0;
	i->target_i = 0;
	i->is_target = OFF;
	return (1);
}	

static	int	fill_token(t_token **token, t_elem *elems)
{
	t_index	i;

	if (!token_malloc(token, elems, &i))
		return (0);
	while (elems)
	{
		if (i.is_target == ON)
		{
			(*token)->target[i.target_i] = elems->element;
			i.target_i++;
			i.is_target = OFF;
		}
		else if (elems->element[0] == '<' || elems->element[0] == '>')
		{
			if (elems->element[0] == '<' && elems->element[1] == '\0')
				(*token)->redir[i.redir_i] = INFILE;
			else if (elems->element[0] == '>' && elems->element[1] == '\0')
				(*token)->redir[i.redir_i] = OUTFILE;
			else if (elems->element[0] == '<' && elems->element[1] == '<')
				(*token)->redir[i.redir_i] = HEREDOC;
			else
				(*token)->redir[i.redir_i] = APPEND;
			i.is_target = ON;
			i.redir_i++;
		}
		else
		{
			(*token)->cmd[i.cmd_i] = elems->element;
			i.cmd_i++;
		}
		elems = elems->next;
	}
	(*token)->cmd[i.cmd_i] = NULL;
	(*token)->redir[i.redir_i] = NO_REDIR;
	(*token)->target[i.target_i] = NULL;
	return (1);
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
	// fill_new(&token, elems);
	if (fill_token(&token, elems) == 0)
	{
		free_token(token);
		return (free_elem(elems));
	}
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
		if (!(tmp->cmd))
			return (free_token(token));
		tmp = tmp->next;
		basic_token = basic_token->next;
	}
	return (token);
}
