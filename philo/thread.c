/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:30:53 by arahmoun          #+#    #+#             */
/*   Updated: 2023/06/14 22:25:25 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_func(int id, t_philo *philos, char *msg)
{
	pthread_mutex_lock(philos->writing);
	printf("%zums   %d  %s\n", get_time() - philos->time, id, msg);
	pthread_mutex_unlock(philos->writing);
}

void	init_var(t_philo **philo, int *i, void *philos)
{
	*philo = (t_philo *)philos;
	*i = (*philo)->i;
}

void	*routine(void *philos)
{
	t_philo	*philo;
	int		i;

	init_var(&philo, &i, philos);
	philo[i].last_meal = get_time();
	if (philo[i].id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(philo[i].fork);
		print_func(i + 1, philo, (char *)"has taken a fork");
		pthread_mutex_lock(philo[(i + 1) % philo->data->number].fork);
		print_func(i + 1, philo, (char *)"has taken a fork");
		print_func(i + 1, philo, (char *)"is eating");
		if (++philo[i].eat == philo[i].data->must)
			philo->total_eat++;
		ft_sleep((size_t)philo->data->eat);
		philo[i].last_meal = get_time();
		pthread_mutex_unlock(philo[(i + 1) % philo->data->number].fork);
		pthread_mutex_unlock(philo[i].fork);
		print_func(i + 1, philo, (char *)"is sleeping");
		ft_sleep((size_t)philo->data->sleep);
		print_func(i + 1, philo, (char *)"is thinking");
	}
	return (0);
}

void	init_philo(int id, t_data *data, t_philo *philos)
{
	philos->data = data;
	philos->total_eat = 0;
	philos->eat = 0;
	philos->time = get_time();
	philos->id = id + 1;
	philos->i = 0;
	philos->time_die = 0;
	philos->time_sleep = 0;
	philos->u_fork = 0;
	philos->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philos->writing = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philos->fork, NULL);
	pthread_mutex_init(philos->writing, NULL);
}

int	creat_thread(t_philo *philos, pthread_t *threads)
{
	philos->i = 0;
	while (philos->i < philos->data->number)
	{
		pthread_create(&threads[philos->i], NULL, &routine, philos);
		usleep(50);
		philos->i++;
		if (philos->i == philos->data->number)
		{
			philos->i--;
			break ;
		}
		usleep(50);
	}
	return (1);
}
