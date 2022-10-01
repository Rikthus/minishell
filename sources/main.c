/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:52:00 by maxperei          #+#    #+#             */
/*   Updated: 2022/10/01 15:22:28 by tulipe           ###   ########lyon.fr   */
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
	if (!expander(&token, env_list) || !heredoc_init(token))
	{
		free_token(token);
		return (free_rd_line(raw_line, BAD_EXIT));
	}
	if (g_herestop == 0)
	{
		if (!exec(token, env_list))
		{
			free_token(token);
			return (free_rd_line(raw_line, BAD_EXIT));
		}
	}
	free_token(token);
	return (free_rd_line(raw_line, GOOD_EXIT));
}


//// WARNING : `cat < infile`   not working if infile doesn't exists
int	main(int argc, char **argv, char **envp)
{
	t_envlist	*env_list;
	int			rl_ret;

	(void)argv;
	g_exit_status = 0;
	signal_mini(BASIC);
	if (argc != 1 || !isatty(1))
		return (err_minishell_usage());
	env_list = make_env(envp);
	if (!env_list)
		return (err_bad_envp_malloc());
	while (1)
	{
		g_herestop = 0;
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
