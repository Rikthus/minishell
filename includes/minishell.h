/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:52:55 by maxperei          #+#    #+#             */
/*   Updated: 2022/08/31 18:51:32 by tulipe           ###   ########lyon.fr   */
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

typedef struct s_base_token
{
	char				*full_cmd;
	struct s_base_token	*next;
}	t_base_token;

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

// CONTROLER
int		controler(char *raw_line, char **envp);

// PRE_PARSING
int		pre_parsing(char *raw_line);

// EXPANDER
void	expand_line(char *raw_line, char **expanded_line, char **envp);


/////////////////////////////////////
//////////     UTILS     ////////////
/////////////////////////////////////

void	change_quote_state(char quote, t_state *state);

#endif
