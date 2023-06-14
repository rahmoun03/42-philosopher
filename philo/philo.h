/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:15:42 by arahmoun          #+#    #+#             */
/*   Updated: 2023/06/14 22:33:22 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
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
	int				i;
	int				total_eat;
	size_t			time;
	size_t			last_meal;
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
void				init_philo(int id, t_data *data, t_philo *philos);
int					just_digit(char **v);
size_t				get_time(void);
void				ft_sleep(size_t timming);
int					ft_error(void);
int					ft_er(void);

#endif
