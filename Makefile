SRC = philo.c ft_atoi.c thread.c

CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=address -g3

all :
	cc ${CFLAGS} ${SRC} -o philo
clean :
	rm -rf a.out philo