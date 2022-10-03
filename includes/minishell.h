/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:52:55 by maxperei          #+#    #+#             */
/*   Updated: 2022/10/04 01:05:24 by tulipe           ###   ########lyon.fr   */
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

// EXIT CASES
# define BAD_EXIT 0
# define GOOD_EXIT 1

// STATE MACHINE
# define OFF 0
# define ON 1
# define CHANGED 1

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

// CMD COUNT EXEC
# define COUNT_ALL 0
# define COUNT_BUILTS 1

// SIGNALS
# define BASIC 0
# define PARENT_STOP 1
# define EXEC 2
# define HEREDOC 3

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
	int				exec_pos;
	char			**cmd;
	int				*redir;
	char			**target;
	int				**hd_pipe;
	struct s_token	*next;
}	t_token;

// EXPANSION STRUCT
typedef struct s_expan
{
	int		left_end;
	int		right_begin;
	int		var_name_index;
	int		*cmd_index;
	char	*left_dup;
	char	*right_dup;
	char	*var_name_dup;
	char	*var_dup;
}	t_expan;

// STATE MACHINE STRUCT
typedef struct s_state
{
	int	sq;
	int	dq;
}	t_state;

// EXEC STRUCT
typedef struct s_env_token
{
	int			old_stdout;
	t_token		*token;
	t_envlist	**envp;
	char		**env;
}	t_env_token;

//GLOBAL
typedef struct s_global
{
	int	exit_status;
	int	herestop;
}	t_global;

t_global	g_shell;

////////////////////////////////////////////////////////////////
//////////    FUNCTION    //////////////////////////////////////
////////////////////////////////////////////////////////////////

// ENV
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
int			join_all(char **str, t_expan exp);
int			expander(t_token **token, t_envlist *env_list);

// TRIM_QUOTES
int			trim_quotes(char **str);

// HEREDOC_INIT
int			heredoc_init(t_token *token);

/////////////////////////////////////
/////////     SIGNALS     ///////////
/////////////////////////////////////
void		signal_mini(int type);

/////////////////////////////////////
//////////     UTILS     ////////////
/////////////////////////////////////

// UTILS
int			cmd_part_len(int *i, char *cmd, int type);
int			free_rd_line(char *line, int ret);
int			change_quote_state(char quote, t_state *state);
char		*custon_strdup(char *str, int start, int end);
int			ft_strcmp(char *s1, char *s2);

// EXPANDER_UTILS
int			init_exp(char **str, t_expan *exp);
int			free_expan(t_expan *exp);
int			comp_var_name(char *env_var, char *dup_var_name);
int			full_line_len(t_expan exp);

// EXPANDER_DUPS
char		*dup_var_name(char *str, int i);
void		cpy_l_and_r(char *str, t_expan *exp);
int			dup_var(char *env_var, t_expan *exp);
void		cpy_full_line(t_expan exp, char **new_line);

// FREE_STRUCT
void		free_basic_token(t_base *basic_token);
void		*free_token(t_token *token);
void		*free_elem(t_elem *elems);
void		free_elem_struct(t_elem *elems);
void		free_env(t_envlist *envlist);

// FREE_MEMORY
void		*free_split_error(char **array, int nb_pointer);
void		*free_2d_array(char **array);
void		free_2d_int_array(int **array, int nb_heredoc);

// PIPE_SPLIT
char		**pipe_split(char *str);

//////////////////////////////////////////////
//////////////      EXEC      ////////////////
//////////////////////////////////////////////

// EXEC
int			exec(t_token *token, t_envlist **envp);

// FIND_ABSOLUTE_PATH
int			find_absolute_path(char **cmd);

// FT_SPLIT_MOD
void		free_all(char **test, int i);
char		**ft_split_mod(char const *s, char c);

// FT_STRJOIN
char		*ft_strjoin_mini(char const *s1, char const *s2);

// PIPES
void		choose_process(t_env_token *e_t,
				int *pipeline, int *pipetmp, int i);

// REDIRECTION
void		redirection(t_env_token *e_t);

char		*env_path(char **envp);
int			find_size_env(t_envlist *env);
char		**custom_envp(t_envlist *envp);
char		*exec_cmd(char **cmds, char *enc_path);
char		*prepare_commands(t_token *token, t_envlist *envp);

// REPLACE EXIT STATUS
int			replace_exit_status(char **str, t_expan exp);

///////////  BUILTINS  //////////
void		choose_process_bltn(t_env_token *env_token,
				int *pipeline, int *pipetmp, int i);
int			choose_builtin(char *str, t_env_token *env_token);
int			ft_pwd(char **argv, t_envlist *env_list);
int			ft_env(char **argv, t_envlist *env_list);
int			ft_unset(char **argv, t_envlist **env_list);
int			ft_echo(char **argv);
int			ft_export(char **argv, t_envlist **env_list);
int			ft_cd(char **argv, t_envlist **env_list);
int			ft_exit(char **argv);

///////////  ERROR  //////////
int			err_no_cmd(t_token *token, char *raw_line);
int			err_minishell_usage(void);
int			err_bad_envp_malloc(void);
int			perror_msg(int err);
int			error_malloc(int err);

#endif
