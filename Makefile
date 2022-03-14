NAME		=	minishell

SRCS		=	minishell.c ms_count_and_record_cmd.c ms_our_cmd.c ms_malloc.c \
				ms_found_env_variable.c  ms_record_array.c ms_cd.c ms_pwd.c \
				ms_get_signal.c ms_exit.c ms_found_redirect.c ms_check_first_arg.c \
				ms_quotation_marks.c ms_execve.c ms_init_env.c ms_export.c \
				ms_execution.c ms_add_env_variable.c ms_free.c ms_unset.c ms_found_variable.c \
				ms_count_arg_divided_qm.c ms_free_all.c ms_utils.c ms_redirect_utils.c \
				ms_print_errors_utils.c ms_record_value.c  ms_builtin_utils.c \
				ms_heredoc.c ms_pipe_and_redirect.c ms_open_file.c ms_check_way_itself.c \
			  	ms_echo.c ms_env.c ms_measure_size_file_name.c ms_print_export.c \
				ms_check_name.c \

OBJS		=	${SRCS:.c=.o}

LIBDIR		=	libft

LIBFT_LIB	=	$(LIBDIR)/libft.a

LIB			=	-L$(LIBDIR) -lft

CC			=	gcc -g

CFLAGS		=	-Wall -Werror -Wextra -I 

RLL			=	-lreadline -L ~/.brew/Cellar/readline/8.1.2/lib \
				-I~/.brew/Cellar/readline/8.1.2/include

RM			=	rm -f

%.o: %.c	Makefile minishell.h
			$(CC) $(CFLAGS)$(LIBDIR) -Iincludes -c $< -o $@

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
test:
		make
		bash ./test/test.sh all


re:			fclean all

.PHONY:		all clean fclean re tools test
