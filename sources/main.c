/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:52:00 by maxperei          #+#    #+#             */
/*   Updated: 2022/09/29 18:35:55 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	syntax_err(char *raw_line)
{
	ft_putstr_fd("Maxine ❤️ : syntax error\n", 2);
	g_exit_status = 258;
	return (free_rd_line(raw_line, GOOD_EXIT));
}

static	int	controler(char *raw_line, t_envlist *env_list)
{
	t_base	*basic_token;
	t_token	*token;

	if (!raw_line)
		return (free_rd_line(raw_line, EOF));
	if (raw_line[0] == '\0')
		return (free_rd_line(raw_line, GOOD_EXIT));
	add_history(raw_line);
	if (!pre_parsing(raw_line))
		return (syntax_err(raw_line));
	basic_token = tokenizer(raw_line);
	if (!basic_token)
		return (free_rd_line(raw_line, BAD_EXIT));
	token = lexer(basic_token);
	free_basic_token(basic_token);
	if (!token)
		return (free_rd_line(raw_line, BAD_EXIT));
	if (!check_tokens(token))
		return (err_no_cmd(token, raw_line));
	if (!expander(&token, env_list) || !heredoc_init(token)
		|| !exec(token, env_list))
	{
		free_token(token);
		return (free_rd_line(raw_line, BAD_EXIT));
	}
	free_token(token);
	return (free_rd_line(raw_line, GOOD_EXIT));
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
	while (1)
	{
		rl_ret = controler(readline("Maxine ❤️ "), env_list);
		if (rl_ret == BAD_EXIT)
		{
			ft_putstr_fd("Malloc failed\n", 2);
			break ;
		}
		else if (rl_ret == EOF)
			break ;
	}
	free_env(env_list);
	rl_clear_history();
	return (0);
}
