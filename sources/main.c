/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:52:00 by maxperei          #+#    #+#             */
/*   Updated: 2022/09/29 15:23:19 by maxperei         ###   ########lyon.fr   */
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

static	int	syntax_err(char *raw_line)
{
	ft_putstr_fd("lol", 1);
	return (free_rd_line(raw_line, GOOD_EXIT));
}

static	int	controler(char *raw_line, t_envlist *env_list)
{
	t_base	*basic_token;
	t_token	*token;

	if (!raw_line)
		return (free_rd_line(raw_line, EOF));
	signal_mini();
	if (raw_line[0] == '\0')
		return (syntax_err(raw_line));
	add_history(raw_line);
	if (!pre_parsing(raw_line))
		return (free_rd_line(raw_line, GOOD_EXIT));
	basic_token = tokenizer(raw_line);
	if (!basic_token)
		return (free_rd_line(raw_line, BAD_EXIT));
	token = lexer(basic_token);
	free_basic_token(basic_token);
	if (!token)
		return (0);
	if (!check_tokens(token))
		return (err_no_cmd(token, raw_line));
	if (!expander(&token, env_list) || !heredoc_init(token))
	{
		free_token(token);
		return (free_rd_line(raw_line, BAD_EXIT));
	}
	//print_tokens(token);
	exec(token, env_list);         //retour erreur
	free_token(token);
	return (free_rd_line(raw_line, GOOD_EXIT));
}

static	void	init_global(t_envlist **env_list)
{
	g_global.exit = 0;
	g_global.env_list = env_list;
}

int	main(int argc, char **argv, char **envp)
{
	t_envlist	*env_list;
	int			rl_ret;

	(void)argv;
	signal_mini();
	if (argc != 1 || !isatty(1))
		return (err_minishell_usage());
	env_list = make_env(envp);
	if (!env_list)
		return (err_bad_envp_malloc());
	init_global(&env_list);
	while (1)
	{
		rl_ret = controler(readline("Maxine <3 "), env_list);
		if (rl_ret == BAD_EXIT)
		{
			ft_putstr_fd("Malloc failed\n", 2);
			break ;
		}
		else if (rl_ret == EOF)
			break ;
	}
	free_env(env_list);
	rl_clear_history();        // necessary ?
	return (0);
}
