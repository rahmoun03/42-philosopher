/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:30:53 by arahmoun          #+#    #+#             */
/*   Updated: 2023/06/14 13:44:30 by arahmoun         ###   ########.fr       */
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
	pthread_mutex_lock(&philos->writing);
	printf("%zums   %d  %s\n", get_time() - philos->time, philos[philos->i].id, msg);
	pthread_mutex_unlock(&philos->writing);
}

void	ft_sleep(size_t timming)
{
	size_t	time;

	time = get_time();
	while (get_time() - time < timming)
		usleep(100);
}

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	if (philo[philo->i].id % 2 == 0)
		usleep(100);
	philo[philo->i].last_meal = get_time();
	while (1)
	{
		pthread_mutex_lock(&philo[philo[philo->i].id - 1].fork);
		print_func(philo, (char *)"has taken a fork");
		pthread_mutex_lock(&philo[philo[philo->i].id % philo->data->number].fork);
		print_func(philo, (char *)"has taken a fork");
		print_func(philo, (char *)"is eating ...");
		if(++philo[philo->i].eat == philo->data->must)
			philo[philo->i].total_eat++;
		ft_sleep((size_t)philo->data->eat);
		philo[philo->i].last_meal = get_time();
		pthread_mutex_unlock(&philo[philo[philo->i].id % philo->data->number].fork);
		pthread_mutex_unlock(&philo[philo[philo->i].id - 1].fork);
		print_func(philo, (char *)"is sleeping");
		ft_sleep((size_t)philo->data->sleep);
		print_func(philo, (char *)"is thinking");
	}
	return (0);
}

void	init_philo(int id, t_data *data, t_philo *philos)
{
	philos->data = data;
	philos->total_eat = 0;
	philos->time = get_time();
	philos->id = id + 1;
	philos->i = 0;
	philos->time_die = 0;
	philos->time_sleep = 0;
	philos->u_fork = 0;
	pthread_mutex_init(&philos->fork, NULL);
	pthread_mutex_init(&philos->writing, NULL);

}

int	creat_thread(t_philo *philos, pthread_t *threads)
{
	philos->i = 0;
	while (philos->i < philos->data->number)
	{
		pthread_create(&threads[philos->i], NULL, routine, philos);
		usleep(100);
		philos->i++;
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
