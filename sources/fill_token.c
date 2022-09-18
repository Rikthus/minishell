/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:40:23 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/18 14:27:31 by maxperei         ###   ########lyon.fr   */
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
	(*token)->target = malloc(sizeof(char *) * (nb_elem(elems, REDIR) + 1));
	if (!((*token)->target))
		return (0);
	(*token)->redir = malloc(sizeof(int) * (nb_elem(elems, REDIR) + 1));
	if (!((*token)->redir))
		return (0);
	(*token)->cmd = malloc(sizeof(char *) * (nb_elem(elems, WORD) + 1));
	if (!((*token)->cmd))
		return (0);
	i->cmd_i = 0;
	i->redir_i = 0;
	i->target_i = 0;
	i->is_target = OFF;
	return (1);
}

static	void	is_redir(t_token **token, t_elem *elems, t_index *i)
{
	if (elems->element[0] == '<' && elems->element[1] == '\0')
		(*token)->redir[i->redir_i] = INFILE;
	else if (elems->element[0] == '>' && elems->element[1] == '\0')
		(*token)->redir[i->redir_i] = OUTFILE;
	else if (elems->element[0] == '>' && elems->element[1] == '>')
		(*token)->redir[i->redir_i] = APPEND;
	else if (elems->element[0] == '<' && elems->element[1] == '<')
		(*token)->redir[i->redir_i] = HEREDOC;
	i->is_target = ON;
	i->redir_i += 1;
}

static	void	is_target(t_token **token, t_elem *elems, t_index *i)
{
	(*token)->target[i->target_i] = elems->element;
	i->target_i += 1;
	i->is_target = OFF;
}

int	fill_token(t_token **token, t_elem *elems)
{
	t_index	i;

	if (!token_malloc(token, elems, &i))
		return (0);
	while (elems)
	{
		if (i.is_target == ON)
			is_target(token, elems, &i);
		else if (elems->element[0] == '<' || elems->element[0] == '>')
			is_redir(token, elems, &i);
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
