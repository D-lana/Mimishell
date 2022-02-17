NAME		=	minishell

SRCS		=	minishell_01.c ms_count_and_record_cmd.c ms_our_cmd.c ms_malloc.c ms_found_env_variable.c  ms_record_array.c ms_cd.c ms_pwd.c\

OBJS		=	${SRCS:.c=.o}

LIBDIR		=	libft

LIBFT_LIB	=	$(LIBDIR)/libft.a

LIB			=	-L$(LIBDIR) -lft

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra -I

RLL			=	-lreadline -L ~/.brew/Cellar/readline/8.1.1/lib \
				-I~/.brew/Cellar/readline/8.1.1/include

RM			=	rm -f

%.o: %.c	Makefile minishell.h
			$(CC) $(CFLAGS)$(LIBDIR) -Iincludes -c $< -o $@
#-Iincludes

$(NAME):	$(LIBFT_LIB) $(OBJS)
			@ $(CC) $(CFLAGS)$(LIBDIR) $(OBJS) -o $(NAME) $(LIB) $(RLL)

all:		$(NAME)

$(LIBFT_LIB):	tools ;

tools:
			make -C $(LIBDIR)

clean:		
			make clean -C $(LIBDIR)
			$(RM) $(OBJS)

fclean:		clean 
			make fclean -C $(LIBDIR)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re tools
