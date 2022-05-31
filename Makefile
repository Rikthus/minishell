NAME	:= minishell

CSAN	:=	-fsanitize=address -g3

CC	:= gcc
CFLAGS	:=	-Wall -Wextra -Werror
RLFLAGS	:=	-L /opt/homebrew/opt/readline/lib #home
RDFLAGS	:=	-I /opt/homebrew/opt/readline/include #home

DIR_SRCS	:=	sources
DIR_INCS	:=	includes
DIR_OBJS	:=	.objs

DIR_LIBFT	:=	libft

LST_SRCS	:=	main.c
LST_INCS	:=	minishell.h
LST_OBJS	:=	$(LST_SRCS:.c=.o)

SRCS	:=	$(addprefix $(DIR_SRCS)/,$(LST_SRCS))
INCS	:=	$(addprefix $(DIR_INCS)/,$(LST_INCS))
OBJS	:=	$(addprefix $(DIR_OBJS)/,$(LST_OBJS))

AR_LIBFT	:=	$(DIR_LIBFT)/libft.a

all	:	make_libft $(NAME)

$(NAME)	:	$(AR_LIBFT) $(OBJS)
			$(CC) $(CFLAGS) $(RDFLAGS) $(RLFLAGS) $^ -o $@ -lreadline

$(LST_OBJS)/%.o	:	$(LST_SRCS)/%.c $(INCS) Makefile | $(DIR_OBJS)
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
