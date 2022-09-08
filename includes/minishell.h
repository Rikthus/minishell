/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:52:55 by maxperei          #+#    #+#             */
/*   Updated: 2022/09/08 14:38:43 by tulipe           ###   ########lyon.fr   */
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

# include "../libft/libft.h"

# define OFF 0
# define ON 1

int	g_status;

typedef struct s_base
{
	char			*full_cmd;
	struct s_base	*next;
}	t_base;

typedef	struct s_token
{
	char			*cmd;
	int				redir;
	char			*target;
	struct s_token	*next;
}	t_token;

typedef	struct s_state
{
	int	sq;
	int	dq;
}	t_state;


/////////////////////////////////////
//////////   PARSING   //////////////
/////////////////////////////////////

// PRE_PARSING
int		pre_parsing(char *raw_line);

// TOKENIZER
void	basic_tokenizer(char *raw_line, t_base **basic_token);

// LEXER

// EXPANDER
char	*expand_line(char *raw_line, char **envp);


/////////////////////////////////////
//////////     UTILS     ////////////
/////////////////////////////////////

void	*free_split_error(char **array, int nb_pointer);
void	free_2d_array(char **array);
void	change_quote_state(char quote, t_state *state);

// PIPE_SPLIT
char	**pipe_split(char *str);

#endif
