# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 16:51:11 by uisroilo          #+#    #+#              #
#    Updated: 2022/06/17 20:48:30 by uisroilo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= main.c check_arguments.c ft_atoi.c init_args.c ft_init_mutex.c \
		ft_create_join.c time.c
OBJS		= $(SRCS:.c=.o)

CC			= gcc -pthread
CFLAGS		= -Wall -Wextra -Werror

RM			= rm -rf

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
	@$(CC) $(OBJS) -o $(NAME) 

clean:
	@$(RM) $(OBJS)

fclean:		clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY: all .c.o clean fclean re