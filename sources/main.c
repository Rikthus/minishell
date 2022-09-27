/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:52:00 by maxperei          #+#    #+#             */
/*   Updated: 2022/09/27 20:05:13 by tulipe           ###   ########lyon.fr   */
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

// static	void	print_env(t_envlist *env_list)
// {
// 	while (env_list)
// 	{
// 		printf("%s\n", env_list->env_var);
// 		env_list = env_list->next;
// 	}
// }

static	int	controler(char *raw_line, t_envlist *env_list)
{
	t_base	*basic_token;
	t_token	*token;

	if (!raw_line)
		return (free_rd_line(raw_line, BAD_EXIT));
	if (raw_line[0] == '\0')
		return (free_rd_line(raw_line, GOOD_EXIT));
	add_history(raw_line);
	if (ft_strncmp("exit", raw_line, 4) == 0)
		exit(0);
	if (!pre_parsing(raw_line))
		return (free_rd_line(raw_line, GOOD_EXIT));
	basic_token = tokenizer(raw_line);
	if (!basic_token)
		return (free_rd_line(raw_line, BAD_EXIT));
	token = lexer(basic_token);
	free_basic_token(basic_token);
	if (!token)
		return (0);
	if (!expander(&token, env_list))
	{
		free_token(token);
		return (free_rd_line(raw_line, BAD_EXIT));
	}
	//print_tokens(token);
	exec(token, env_list); //retour erreur
	free_token(token);
	return (free_rd_line(raw_line, GOOD_EXIT));
}

int	main(int argc, char **argv, char **envp)
{
	t_envlist	*env_list;

	(void)argv;
	signal_mini();
	if (argc != 1 || !isatty(1))
	{
		printf("Usage: ./minishell\n");
		return (0);
	}
	env_list = make_env(envp);
	if (!env_list)
	{
		printf("ERROR\n");
		return (0);
	}
	while (1)
	{
		// signal_exec(); PUT INSIDE EXEC
		if (!controler(readline("Maxine <3 "), env_list))
			break ;
	}
	free_env(env_list);
	return (0);
}
