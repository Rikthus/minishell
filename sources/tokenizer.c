/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:40:25 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/08 15:41:24 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	t_base	*add_btoken(char *cmd)
{
	t_base	*new;

	new = malloc(sizeof(t_base));
	if (!new)
		return (NULL);
	new->full_cmd = cmd;
	new->next = NULL;
	return (new);	
}

static	void	*error_case(char **splitted_line, t_base *basic_token)
{
	t_base	*previous;
	
	while (basic_token)
	{
		previous = basic_token;
		basic_token = basic_token->next;
		free(previous);
	}
	free_2d_array(splitted_line);
	return (NULL);
}

t_base	*tokenizer(char *raw_line)
{
	t_base	*basic_token;
	t_base	*tmp;
	char	**splitted_line;
	int		i;

	splitted_line = pipe_split(raw_line);
	if (!splitted_line)
		return (NULL);
	basic_token = add_btoken(splitted_line[0]);
	if (!basic_token)
		return (free_2d_array(splitted_line));
	tmp = basic_token;
	i = 1;
	while (splitted_line[i])
	{
		tmp->next = add_btoken(splitted_line[i]);
		if (!(tmp->next))
			return (error_case(splitted_line, basic_token));
		tmp = tmp->next;
		i++;
	}
	free(splitted_line);
	return (basic_token);
}