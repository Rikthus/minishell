NAME	:= minishell

CSAN	:=	-fsanitize=address -g3

CC	:= gcc
CFLAGS	:=	-Wall -Wextra -Werror
RLFLAGS		:=	-L /opt/homebrew/opt/readline/lib #max_home
RDFLAGS		:=	-I /opt/homebrew/opt/readline/include #max_home
#RLFLAGS	:=	-L /Users/maxperei/Desktop/Logiciels/homebrew/opt/readline/lib #max_42
#RDFLAGS	:=	-I /Users/maxperei/Desktop/Logiciels/homebrew/opt/readline/include #max_42
#RLFLAGS	:=	-L /usr/local/opt/readline/lib #cha_home
#RDFLAGS	:=	-I /usr/local/opt/readline/include #cha_home
#RLFLAGS	:=	-L /Users/cdutel-l/.brew/opt/readline/lib #cha_42
#RDFLAGS	:=	-I /Users/cdutel-l/.brew/opt/readline/include #cha_42

DIR_SRCS	:=	sources
DIR_INCS	:=	includes
DIR_OBJS	:=	.objs

DIR_LIBFT	:=	libft

LST_SRCS	:=	main.c				\
				utils.c				\
				pipe_split.c		\
				controler.c			\
				pre_parsing.c	
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
			rm -rf $(NAME)
			$(MAKE) fclean -C $(DIR_LIBFT)

re	:
		$(MAKE) fclean
		$(MAKE) all

.PHONY	:	all make_libft clean fclean re
