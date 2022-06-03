/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:52:55 by maxperei          #+#    #+#             */
/*   Updated: 2022/06/03 19:27:21 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

# define STOP_SHELL 0
# define RET_PROMPT 1

# define BAD_SYNTAX 0

int	g_status = 0;

// typedef enum e_error
// {

// }	t_error;

typedef enum e_tok
{
	cmd = 0,
	arg = 1,
	single_q = 2,
	double_q = 3,
}	t_tok;

typedef enum e_redir
{
	red_in = 0,
	red_out = 1,
	append_in = 2,
	here_doc = 3,
	pipeline = 4,
}	t_redir;

typedef enum e_builtin
{
	cmd_echo = 0,
	cmd_cd = 1,
	cmd_pwd = 2,
	cmd_export = 3,
	cmd_unset = 4,
	cmd_env = 5,
	cmd_exit = 6,
}	t_builtin;

typedef struct s_token
{
	char			*literal;
	t_redir			redir_type;
	char			*redir_file;
	int				expand;
	struct	s_token	*next;
}	t_token;

// SHELL
int	shell(char *line, char **envp);

// TOKENIZER
int	tokenizer(t_tokens **tokens, char *line, char **envp);

#endif
