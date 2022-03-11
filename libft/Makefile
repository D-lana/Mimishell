# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlana <dlana@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/02 21:56:09 by dlana             #+#    #+#              #
#    Updated: 2022/03/10 22:02:41 by dlana            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

CC			=	gcc
RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror

SRCS		=	ft_strlen.c ft_isdigit.c ft_strncmp.c ft_itoa.c ft_strdup.c ft_split.c ft_strjoin.c\
				ft_atoi.c ft_isalpha.c ft_strchr.c ft_putstr_fd.c ft_putnbr_fd.c ft_ll_atoi.c\

OBJS		=	${SRCS:.c=.o}

HEADER		=  -I libft.h

.c.o:		= Makefile libft.h
			${CC} ${CFLAGS} -c $< ${HEADER} -o ${<:.c=.o} 

${NAME}:	${OBJS}
			ar rcs ${NAME} ${OBJS}

all:		${NAME}
	
clean:	
			${RM} ${OBJS} 
			
fclean:		clean
			${RM} ${NAME} 

re:			fclean all

.PHONY: all clean fclean re bonus