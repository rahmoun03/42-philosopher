/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:25:52 by arahmoun          #+#    #+#             */
/*   Updated: 2023/06/14 22:34:05 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(void)
{
	printf("Error : %syou must at less ", YOLLOW);
	printf("enter 5 argument%s\n", DEFFAULT);
	return (1);
}

void	dest_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->number)
	{
		pthread_mutex_destroy(philo[i].fork);
		pthread_mutex_destroy(philo[i].writing);
		free(philo[i].fork);
		free(philo[i].writing);
		i++;
	}
}

void	loop_func(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo->total_eat == philo->data->number)
		{
			dest_mutex(philo);
			return ;
		}
		if (get_time() - philo[i].last_meal >= (size_t)data->death)
		{
			usleep(100);
			pthread_mutex_lock(philo->writing);
			printf("%zums	%d died", get_time() - philo->time, philo->id);
			pthread_mutex_unlock(philo->writing);
			dest_mutex(philo);
			return ;
		}
		i = (i + 1) % data->number;
		usleep(100);
	}
}

int	start_t(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		init_philo(i, data, &philos[i]);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	*threads;
	t_philo		*philos;

	if (ac == 5 || ac == 6)
	{
		if (just_digit(av))
			return (ft_er());
		data = init_data(av, ac);
		if (check_data(ac, data))
			return (1);
		threads = (pthread_t *)malloc(sizeof(pthread_t) * (data->number));
		philos = (t_philo *)malloc(sizeof(t_philo) * (data->number));
		start_t(data, philos);
		creat_thread(philos, threads);
		loop_func(philos, data);
	}
	else
		ft_error();
}
