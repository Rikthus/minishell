/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:40:22 by tulipe            #+#    #+#             */
/*   Updated: 2022/08/31 18:42:16 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	controler(char *raw_line, char **envp)
{
	//t_base_token	*basic_token;
	//t_token			*token;
	//char			*expanded_line;
	(void)envp;
	
	if (!pre_parsing(raw_line))
	{
		printf("ERROR\n");
		return (0);
	}
	// expand_line(raw_line, &expanded_line, envp);
	// if (!expanded_line)
	// 	return (0);
	// if (!valid_char(expanded_line)
	//	{
	//		free(expanded_line);
	//		return (0);
	//	}
	// base_parse(expanded_line, &basic_token);
	// free(expanded_line);
	// if (!basic_token)
	// 	return (0);
	// deep_parse(&basic_token, &token);
	// free_basic_token(basic_token);
	// if (!token)
	// 	return (0);
	return (1);
}