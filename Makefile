NAME		=	minishell

<<<<<<< HEAD
SRCS		=	minishell.c ms_count_and_record_cmd.c ms_our_cmd.c ms_malloc.c \
				ms_found_env_variable.c proba.c ms_record_array.c ms_quotation_marks.c \
				ms_found_redirect.c \
=======
SRCS		=	minishell_01.c ms_count_and_record_cmd.c ms_our_cmd.c ms_malloc.c ms_found_env_variable.c proba.c ms_record_array.c\
>>>>>>> bb40ce35152e5b5a6a6fc93d5286df298bdbc842

OBJS		=	${SRCS:.c=.o}

LIBDIR		=	libft

LIBFT_LIB	=	$(LIBDIR)/libft.a

LIB			=	-L$(LIBDIR) -lft

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra -I

RLL			=	-lreadline -L ~/.brew/Cellar/readline/8.1.2/lib \
				-I~/.brew/Cellar/readline/8.1.2/include

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
