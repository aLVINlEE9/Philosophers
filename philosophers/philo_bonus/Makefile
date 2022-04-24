# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 01:59:37 by seungsle          #+#    #+#              #
#    Updated: 2022/04/24 23:17:30 by seungsle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus
CC		= gcc -g
CFLAG	= -Werror -Wall -Wextra
SRCS 	=	srcs/init.c		\
			srcs/main.c		\
			srcs/philo.c 	\
			srcs/print.c 	\
			srcs/process.c 	\
			srcs/util.c

OBJS 	= ${SRCS:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $(NAME)

.c.o:
	$(CC) $(CFLAG) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re