/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:52:55 by maxperei          #+#    #+#             */
/*   Updated: 2022/09/21 18:17:49 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// SYSTEM LIBRARY
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

// CUSTOM LIBRARY
# include "../libft/libft.h"

// STATE MACHINE
# define OFF 0
# define ON 1

// REDIRECTION TYPES
# define NO_REDIR -1
# define OUTFILE 0 // >
# define APPEND 1  // >>
# define INFILE 2  // <
# define HEREDOC 3 // <<

// LEN TYPE
# define WORD 0
# define REDIR 1
# define QUOTE 2

// ELEM TO EXPAND
# define CMD 0
# define TARGET 1

// PIPE POSITION
# define NO_PIPE -1
# define FIRST_CMD 0
# define LAST_CMD 1
# define INTER_CMD 2

int	g_status;

//CUSTOM ENVP
typedef struct s_envlist
{
	char				*env_var;
	struct s_envlist	*next;
}	t_envlist;

// TOKENIZER STRUCT
typedef struct s_base
{
	char			*full_cmd;
	struct s_base	*next;
}	t_base;

// PRE_LEXING STRUCT
typedef struct s_elem
{
	char			*element;
	struct s_elem	*next;
}	t_elem;

// TOKEN INDEX STRUCT
typedef struct s_index
{
	int	cmd_i;
	int	redir_i;
	int	target_i;
	int	is_target;
}	t_index;

// LEXER STRUCT
typedef struct s_token
{
	int				pipe_pos;
	char			**cmd;
	int				*redir;
	char			**target;
	struct s_token	*next;
}	t_token;

// STATE MACHINE STRUCT
typedef struct s_state
{
	int	sq;
	int	dq;
}	t_state;

////////////////////////////////////////////////////////////////
//////////    FUNCTION    //////////////////////////////////////
////////////////////////////////////////////////////////////////

t_envlist	*make_env(char **envp);

/////////////////////////////////////
//////////   PARSING   //////////////
/////////////////////////////////////

// PRE_PARSING
int			pre_parsing(char *raw_line);

// TOKENIZER
t_base		*tokenizer(char *raw_line);

// LEXER
t_token		*lexer(t_base *basic_token);
t_elem		*break_cmd(char *full_cmd);
int			fill_token(t_token **token, t_elem *elems);

// EXPANSION
int		*expander(t_token **token, t_envlist *env_list);

/////////////////////////////////////
//////////     UTILS     ////////////
/////////////////////////////////////

int			cmd_part_len(int *i, char *cmd, int type);
int			free_rd_line(char *line, int ret);
void		change_quote_state(char quote, t_state *state);

// FREE_STRUCT
void		free_basic_token(t_base *basic_token);
void		*free_token(t_token *token);
void		*free_elem(t_elem *elems);
void		free_elem_struct(t_elem *elems);
void		free_env(t_envlist *envlist);

// FREE_MEMORY
void		*free_split_error(char **array, int nb_pointer);
void		*free_2d_array(char **array);

// PIPE_SPLIT
char		**pipe_split(char *str);

#endif
