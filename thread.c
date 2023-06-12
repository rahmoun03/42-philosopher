/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:30:53 by arahmoun          #+#    #+#             */
/*   Updated: 2023/06/12 12:11:37 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_func(t_philo *philos, char *msg)
{
	pthread_mutex_lock(philos->writing);
	printf("%zums   %d  %s\n", get_time() - philos->time, philos->id, msg);
	pthread_mutex_unlock(philos->writing);
}
void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	if (philo->id % 2 == 0)
		usleep(10);
	philo->time_meal = get_time();
	while (1)
	{
		pthread_mutex_lock(&philo->fork[philo->id - 1]);
		print_func(philo, (char *)"has taken a fork");
		pthread_mutex_lock(&philo->fork[philo->id % philo->data->number]);
		print_func(philo, (char *)"has taken a fork");
		print_func(philo, (char *)"is eating ...");
		if(philo->eat++ == philo->data->must)
			philo->total_eat++;
		usleep(philo->data->eat * 1000);
		philo->time_meal = get_time();
		pthread_mutex_unlock(&philo->fork[philo->id % philo->data->number]);
		pthread_mutex_unlock(&philo->fork[philo->id - 1]);
		print_func(philo, (char *)"is sleeping");
		usleep(philo->data->sleep * 1000);
		print_func(philo, (char *)"is thinking");
	}
	return (0);
}

void	init_philo(int id, t_data *data, t_philo *philos)
{
	int i;

	philos->data = data;
	philos->total_eat = 0;
	philos->time = get_time();
	philos->id = id + 1;
	philos->time_die = 0;
	philos->time_sleep = 0;
	philos->u_fork = 0;
	i = 0;
	philos->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->number);
	philos->writing = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->number);
	while (i < data->number)
	{
		pthread_mutex_init(&philos->fork[i], NULL);
		pthread_mutex_init(&philos->writing[i], NULL);
		i++;
	}
}

int	creat_thread(t_philo *philos, pthread_t *threads)
{
	int		i;

	i = 0;
	while (i < philos->data->number)
	{
		pthread_create(&threads[i], NULL, routine, &philos[i]);
		usleep(100);
		i++;
	}
	return (1);
}

int	start_t(t_data *data, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < data->number)
	{
		init_philo(i, data, &philos[i]);
		i++;
	}
	return (1);
}
