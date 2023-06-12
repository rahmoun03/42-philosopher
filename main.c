/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:25:52 by arahmoun          #+#    #+#             */
/*   Updated: 2023/06/12 12:06:24 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(void)
{
	printf("Error : %syou must at less ", YOLLOW);
	printf("enter 5 argument%s\n", DEFFAULT);
	return (1);
}

void	loop_func(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo[i].total_eat == philo[i].data->number)
		{
			// dest_mutex(philo);
			// free_param(philo, philo->mutex, var);
			return ;
		}
		if (get_time() - philo[i].time_meal
			> (size_t )data->death)
		{
			usleep(100);
			pthread_mutex_lock(philo->writing);
			printf("%zums	%d died", get_time() - philo->time, philo->id);
			// dest_mutex(philo);
			// free_param(philo, philo->mutex, var);
			return ;
		}
		i = (i + 1) % data->number;
		usleep(500);
	}
}

int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	*threads;
	t_philo		*philos;
	
	if (ac == 5 || ac == 6)
	{
		if (just_digit(av))
			return (ft_error());
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
