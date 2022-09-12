/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:52:00 by maxperei          #+#    #+#             */
/*   Updated: 2022/09/13 01:32:06 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static	void	print_tokens(t_token *token)
// {
// 	int	i;
// 	int	j;
	
// 	while (token)
// 	{
// 		i = 0;
// 		j = 0;
// 		while (token->cmd[i])
// 		{
// 			printf("%s\n", token->cmd[i]);
// 			i++;
// 		}
// 		printf("\n");
// 		while (token->target[j])
// 		{
// 			printf("%d   %s\n", token->redir[j], token->target[j]);
// 			j++;
// 		}
// 		printf("\n\n\n");
// 		token = token->next;
// 	}
// }

static	int	controler(char *raw_line, char **envp)
{
	t_base	*basic_token;
	t_token	*token;
	(void)envp;

	if (!raw_line || raw_line[0] == '\0' || !pre_parsing(raw_line))
		return (free_rd_line(raw_line, 0));
	basic_token = tokenizer(raw_line);
	if (!basic_token)
		return (free_rd_line(raw_line, 0));
	token = lexer(basic_token);
	free_basic_token(basic_token);
	if (!token)
		return (0);
	// print_tokens(token);
	// expander(&token, envp);
	// free_token (and free token if fail exec too)
	return (free_rd_line(raw_line, 1));
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	g_status = 0;
	if (argc != 1)
	{
		printf("Usage: ./minishell\n");
		return (g_status);
	}
	while (1)
	{
		////////////////// PARSING '/' char
		///////////////// PARSING redir parsing
		controler(readline("Maxine <3 "), envp);
	}
	return (g_status);
}
