/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:52:55 by maxperei          #+#    #+#             */
/*   Updated: 2022/08/30 19:46:53 by tulipe           ###   ########lyon.fr   */
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

int	g_status = 0;

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

/////////////////////////////////////
//////////   PARSING   //////////////
/////////////////////////////////////

// EXPANDER
void	expand_line(char *raw_line, char **expanded_line);

#endif
