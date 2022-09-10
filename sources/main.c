/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:52:00 by maxperei          #+#    #+#             */
/*   Updated: 2022/09/10 17:25:24 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	print_list(t_base *list)
{
	while (list)
	{
		printf("%s\n\n", list->full_cmd);
		list = list->next;
	}
}

static	int	controler(char *raw_line, char **envp)
{
	t_base	*basic_token;
	// t_token	*token;
	(void)envp;

	if (!raw_line || raw_line[0] == '\0' || !pre_parsing(raw_line))
		return (0);
	basic_token = tokenizer(raw_line);
	if (!basic_token)
		return (0);
	print_list(basic_token);
	// token = lexer(basic_token);
	free_basic_token(basic_token);
	// if (!token)
	// 	return (0);
	// expander(&token);
	return (1);
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
					//////////////////////////////////////////
					////  ERRORRRRR FOR EMPTY LINE INPUT  ////
					//////////////////////////////////////////
		controler(readline("Maxine <3 "), envp);
	}
	return (g_status);
}
