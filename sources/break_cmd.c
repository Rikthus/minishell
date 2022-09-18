/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:12:45 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/16 13:51:14 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	*dup_quoted(int *i, char *cmd)
{
	char	*dup;
	char	quote;
	int		j;

	if (cmd[*i] == '$')
		*i += 1;
	dup = malloc(sizeof(char) * (cmd_part_len(i, cmd, QUOTE) + 1));
	if (!dup)
		return (NULL);
	quote = cmd[*i];
	j = 0;
	dup[j] = cmd[*i];
	*i += 1;
	j++;
	while (cmd[*i] != quote)
	{
		dup[j] = cmd[*i];
		*i += 1;
		j++;
	}
	dup[j] = cmd[*i];
	*i += 1;
	j++;
	dup[j] = '\0';
	return (dup);
}

static	char	*dup_redir(int *i, char *cmd)
{
	char	*dup;
	int		j;

	dup = malloc(sizeof(char) * (cmd_part_len(i, cmd, REDIR) + 1));
	if (!dup)
		return (NULL);
	j = 0;
	while (cmd[*i] == '<' || cmd[*i] == '>')
	{
		dup[j] = cmd[*i];
		*i += 1;
		j++;
	}
	dup[j] = '\0';
	return (dup);
}

static	char	*cmd_part_dup(int *i, char *cmd)
{
	char	*dup;
	int		j;
	
	if (cmd[*i] == '<' || cmd[*i] == '>')
		return (dup_redir(i, cmd));
	else if (cmd[*i] == '\'' || cmd[*i] == '\"')
		return (dup_quoted(i, cmd));
	else if (cmd[*i] == '$' && (cmd[*i + 1] == '\'' || cmd[*i + 1] == '\"'))
		return (dup_quoted(i, cmd));
	else
	{
		dup = malloc(sizeof(char) * (cmd_part_len(i, cmd, WORD) + 1));
		if (!dup)
			return (NULL);
		j = 0;
		while (cmd[*i] && !ft_isspace(cmd[*i]) && cmd[*i] != '\''
			&& cmd[*i] != '\"' && cmd[*i] != '<' && cmd[*i] != '>')
		{
			dup[j] = cmd[*i];
			*i += 1;
			j++;
		}
		dup[j] = '\0';
		return (dup);	
	}	
}

static	t_elem	*add_elem(int *i, char *full_cmd)
{
	t_elem	*new_elem;

	new_elem = malloc(sizeof(t_elem));
	if (!new_elem)
		return (NULL);
	new_elem->next = NULL;
	new_elem->element = cmd_part_dup(i, full_cmd);
	if (!(new_elem->element))
	{
		free(new_elem);
		return (NULL);
	}
	return (new_elem);
}

t_elem	*break_cmd(char *full_cmd)
{
	t_elem	*elems;
	t_elem	*tmp;
	int		i;

	i = 0;
	while (ft_isspace(full_cmd[i]))
		i++;
	elems = add_elem(&i, full_cmd);
	if (!elems)
		return (NULL);
	tmp = elems;
	while (full_cmd[i])
	{
		if (ft_isspace(full_cmd[i]))
			i++;
		else
		{
			tmp->next = add_elem(&i, full_cmd);
			if (!(tmp->next))
				return (free_elem(elems));
			tmp = tmp->next;
		}		
	}
	return (elems);
}