NAME	:= minishell

CSAN	:=	-fsanitize=address -g3

CC	:= gcc
CFLAGS	:=	-Wall -Wextra -Werror #$(CSAN)
# RLFLAGS	:=	-L /opt/homebrew/opt/readline/lib #max_home
# RDFLAGS	:=	-I /opt/homebrew/opt/readline/include #max_home
RLFLAGS	:=	-L /Users/maxperei/Desktop/Logiciels/homebrew/opt/readline/lib #max_42
RDFLAGS	:=	-I /Users/maxperei/Desktop/Logiciels/homebrew/opt/readline/include #max_42
# RLFLAGS	:=	-L /usr/local/opt/readline/lib #cha_home
# RDFLAGS	:=	-I /usr/local/opt/readline/include #cha_home
# RLFLAGS	:=	-L /Users/cdutel-l/.brew/opt/readline/lib #cha_42
# RDFLAGS	:=	-I /Users/cdutel-l/.brew/opt/readline/include #cha_42

DIR_SRCS	:=	sources
DIR_INCS	:=	includes
DIR_OBJS	:=	.objs

DIR_LIBFT	:=	libft

LST_SRCS	:=	main.c				\
				make_env.c			\
				utils.c				\
				free_struct.c		\
				free_memory.c		\
				pipe_split.c		\
				pre_parsing.c		\
				tokenizer.c			\
				lexer.c				\
				break_cmd.c			\
				fill_token.c		\
				trim_quotes.c		\
				expander.c			\
				expander_utils.c	\
				expander_dups.c		\
				signals.c			\
				heredoc_init.c		\
				e_exec.c			\
				e_find_absolute_path.c	\
				e_ft_split_mod.c	\
				e_ft_strjoin.c		\
				e_pipes.c			\
				e_redirection.c		\
				e_utils_exec.c		\
				error_msg.c			\
				rplc_exit_status.c	\
				bltn_cd.c			\
				bltn_echo.c			\
				bltn_env.c			\
				bltn_exit.c			\
				bltn_export.c		\
				bltn_pwd.c			\
				bltn_unset.c		\
				builtin_redir.c
LST_INCS	:=	minishell.h
LST_OBJS	:=	$(LST_SRCS:.c=.o)

SRCS	:=	$(addprefix $(DIR_SRCS)/,$(LST_SRCS))
INCS	:=	$(addprefix $(DIR_INCS)/,$(LST_INCS))
OBJS	:=	$(addprefix $(DIR_OBJS)/,$(LST_OBJS))

AR_LIBFT	:=	$(DIR_LIBFT)/libft.a

all	:	make_libft $(NAME)

$(NAME)	:	$(AR_LIBFT) $(OBJS)
			$(CC) $(CFLAGS) $(RDFLAGS) $(RLFLAGS) $^ -o $@ -lreadline

$(DIR_OBJS)/%.o	:	$(DIR_SRCS)/%.c $(INCS) Makefile | $(DIR_OBJS)
					$(CC) $(CFLAGS) $(RDFLAGS) -I $(LST_INCS) -c $< -o $@

$(AR_LIBFT)	:
				$(MAKE) -C $(DIR_LIBFT)

$(DIR_OBJS)	:
				mkdir -p $(DIR_OBJS)

make_libft	:
				$(MAKE) -C $(DIR_LIBFT)

clean	:
			rm -rf $(DIR_OBJS)
			$(MAKE) clean -C $(DIR_LIBFT)

fclean	:
			$(MAKE) clean
			rm -rf $(NAME)
			$(MAKE) fclean -C $(DIR_LIBFT)

re	:
		$(MAKE) fclean
		$(MAKE) all

.PHONY	:	all make_libft clean fclean re
