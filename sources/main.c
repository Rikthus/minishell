/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:52:00 by maxperei          #+#    #+#             */
/*   Updated: 2022/09/08 14:43:22 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	print_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		printf("%s\n\n", split[i]);
		i++;
	}
}

static	int	controler(char *raw_line, char **envp)
{
	// t_base	*basic_token;
	//t_token	*token;
	(void)envp;
	
	if (!pre_parsing(raw_line))
	{
		printf("ERROR\n");
		return (0);
	}
	
	char	**split;
	split = pipe_split(raw_line);
	print_split(split);
	// basic_tokenizer(raw_line, &basic_token);
	// if (!basic_token)
	// 	return (0);
	// deep_parse(&basic_token, &token);
	// free_basic_token(basic_token);
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
		controler(readline("Maxine <3 "), envp);
	}
	return (g_status);
}
