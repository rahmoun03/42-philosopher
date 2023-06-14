# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 21:37:12 by arahmoun          #+#    #+#              #
#    Updated: 2023/06/14 22:11:16 by arahmoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philo.c ft_atoi.c thread.c main.c

CFLAGS = -Wall -Wextra -Werror -pthread

${NAME} : $(SRC)
	@cc ${CFLAGS} ${SRC} -o philo
	@tput setaf 2; echo "philo is ready"
	
all : ${NAME}

fclean : clean

clean :
	@rm -rf philo
	@tput setaf 1; echo "Clean"
	
re : fclean all