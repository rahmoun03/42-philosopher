#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
# define RED "\033[7m\033[31m"
# define BLUE "\033[7m\033[34m"
# define DEFFAULT "\033[0m"
# define GREEN "\033[7m\033[32m"
# define YOLLOW "\033[7m\033[33m"

typedef struct s_data
{
	int				sleep;
	int				eat;
	int				death;
	int				number;
	int				must;
	pthread_mutex_t	mutex;
}                   t_data;

typedef struct s_philo
{
	int             id;
	pthread_t       threads;
	t_data          *data;
	pthread_mutex_t fork;
	struct s_philo  *next;
}                   t_philo;

int ft_atoi(const char *str);
int start_t (int ac, char **av);

#endif
