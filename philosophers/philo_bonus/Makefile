# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 20:00:26 by seungsle          #+#    #+#              #
#    Updated: 2022/03/21 20:07:46 by seungsle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus
CC		= gcc
CFLAG	= -Werror -Wall -Wextra
SRCS 	= 

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