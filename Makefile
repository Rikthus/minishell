##########################
#    BASIC VARIABLES     #
##########################

CSAN		:=	-fsanitize=address -g3

NAME		:=	minishell
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror #$(CSAN)

RLLIB	:=	-L /opt/homebrew/opt/readline/lib -l readline#max_home
RLINC	:=	-I /opt/homebrew/opt/readline/include #max_home
# RLLIB	:=	-L /Users/maxperei/Desktop/Logiciels/homebrew/opt/readline/lib -l readline #max_42
# RLINC	:=	-I /Users/maxperei/Desktop/Logiciels/homebrew/opt/readline/include #max_42
# RLLIB	:=	-L /usr/local/opt/readline/lib -l readline #cha_home
# RLINC	:=	-I /usr/local/opt/readline/include #cha_home
# RLLIB	:=	-L /Users/cdutel-l/.brew/opt/readline/lib -l readline #cha_42
# RLINC	:=	-I /Users/cdutel-l/.brew/opt/readline/include #cha_42

INCFLAGS	=	$(RLINC) -I $(D_INCS)
LIBFLAGS	=	$(RLLIB)
AR_LIBFT	=	$(D_LIBFT)libft.a

RM			:=	rm -rf

############################
#        FILE TREE         #
############################

# files

LST_BUILTINS	:=	bltn_cd_utils.c		bltn_cd.c		bltn_echo.c			\
					bltn_env.c			bltn_exit.c		bltn_export_utils.c	\
					bltn_export.c		bltn_pwd.c		bltn_unset.c

LST_EXEC		:=	builtin_redir.c		e_builtin_redirection.c		e_exec_dlc.c		\
					e_exec.c			e_find_absolute_path.c		e_ft_split_mod.c	\
					e_ft_strjoin.c		e_pipes.c					e_redirection.c		\
					e_utils_exec.c

LST_PARSING		:=	break_cmd.c			error_msg.c			expander_dups.c		\
					expander_utils.c	expander.c			fill_token.c		\
					free_memory.c		free_struct.c		heredoc_init.c		\
					heredoc_utils.c		lexer.c				make_env.c			\
					pipe_split.c		pre_parsing.c		rplc_exit_status.c	\
					signals.c			tokenizer.c			trim_quotes.c		\
					utils_lib.c			utils.c

LST_MAIN		:=	main.c

LST_INCS		:=	minishell.h
LST_OBJS		=	$(SRCS:.c=.o)

# directories

D_LIBFT	:=	libft/

D_SRCS	:=	sources/
D_INCS	:=	includes/
D_OBJS	:=	.objs/

D_BUILTINS	:=	builtins/
D_EXEC		:=	exec/
D_PARSING	:=	parsing/

# full paths

SRCS	=	$(addprefix $(D_SRCS)$(D_BUILTINS),$(LST_BUILTINS))	\
			$(addprefix $(D_SRCS)$(D_EXEC),$(LST_EXEC))			\
			$(addprefix $(D_SRCS)$(D_PARSING),$(LST_PARSING))	\
			$(addprefix $(D_SRCS),$(LST_MAIN))
INCS	=	$(addprefix $(D_INCS),$(LST_INCS))
OBJS	=	$(subst $(D_SRCS),$(D_OBJS),$(LST_OBJS))

##########################
#         RULES          #
##########################

all	:	makelibft $(NAME)

$(NAME)	:	$(OBJS) $(AR_LIBFT) $(INCS) Makefile
			$(CC) $(CFLAGS) $(LIBFLAGS) $(INCFLAGS) $(AR_LIBFT) $(OBJS) -o $@

$(D_OBJS)%.o	:	$(D_SRCS)%.c $(INCS) $(AR_LIBFT) Makefile | $(D_OBJS)
					$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(D_OBJS)		:
					mkdir -p $(D_OBJS)	\
					$(D_OBJS)$(D_BUILTINS)	$(D_OBJS)$(D_EXEC)	$(D_OBJS)$(D_PARSING)

$(AR_LIBFT)		:
					$(MAKE) -C $(D_LIBFT)

makelibft		:
					$(MAKE) -C $(D_LIBFT)

clean	:
			$(RM) $(OBJS)
			$(RM) $(D_OBJS)

fclean	:
			$(MAKE) clean
			$(RM) $(NAME)
			$(MAKE) fclean -C $(D_LIBFT)

re	:
		$(MAKE) fclean
		$(MAKE) all

.PHONY	:	all makelibft clean fclean re
