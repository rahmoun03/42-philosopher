#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# define RED "\033[7m\033[31m"
# define BLUE "\033[7m\033[34m"
# define DEFFAULT "\033[0m"
# define GREEN "\033[7m\033[32m"
# define YOLLOW "\033[33m"


typedef struct s_data
{
	int				number;
	int				death;
	int				eat;
	int				sleep;
	int				must;
}					t_data;

typedef struct s_philo
{
	int				eat;
	int				total_eat;
	size_t			time;
	size_t			time_meal;
	int				time_sleep;
	int				time_die;
	int				id;
	t_data			*data;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*writing;
	int				u_fork;
}					t_philo;


int					check_data(int ac, t_data *data);
t_data				*init_data(char **av, int ac);
int					ft_atoi(const char *str);
int					start_t(t_data *data, t_philo *philos);
int					creat_thread(t_philo *philos, pthread_t *threads);
int					just_digit(char **v);
size_t				get_time(void);
int					ft_error(void);


#endif
