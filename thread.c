/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:30:53 by arahmoun          #+#    #+#             */
/*   Updated: 2023/06/08 14:17:16 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		g_all = 0;

int	get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_usec);
}

void	*routine(void *philos)
{
	t_philo	*tmp;
	
	tmp = (t_philo *)philos;
	tmp->time = get_time();
	while(1)
	{
		if (tmp->u_fork == 0)
		{
			pthread_mutex_lock(&tmp->fork);
			tmp->u_fork = 1;
			if (tmp->next->u_fork == 0)
			{
				tmp->next->u_fork = 1;
				pthread_mutex_lock(&tmp->next->fork);
				printf("creating thread, %d\n", tmp->id);
				for (int i = 0; i < 4; i++)
				{
					printf("%d philo %d is working %d time\n", tmp->time, tmp->id, i + 1);
				}
				g_all++;
				pthread_mutex_unlock(&tmp->next->fork);
				tmp->next->u_fork = 0;
			}
			pthread_mutex_unlock(&tmp->fork);
			tmp->u_fork = 0;
		}
	}
	return (philos);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new_)
{
	t_philo	*tmp;

	if (!*lst)
	{
		(*lst) = new_;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_;
}

t_philo	*init_philo(int id, int ac, char **av, t_philo *last)
{
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo));
	philos->data = (t_data *)malloc(sizeof(t_data));
	philos->id = id;
	philos->time = 0;
	philos->time_die = 0;
	philos->time_sleep = 0;
	philos->u_fork = 0;
	pthread_mutex_init(&philos->fork, NULL);
	philos->data->number = ft_atoi(av[1]);
	philos->data->death = ft_atoi(av[2]);
	philos->data->eat = ft_atoi(av[3]);
	philos->data->sleep = ft_atoi(av[4]);
	if (ac == 6)
		philos->data->must = ft_atoi(av[5]);
	else
		philos->data->must = -1;
	pthread_mutex_init(&philos->data->mutex, NULL);
	philos->next = last;
	return (philos);
}

int	creat_thread(t_philo *philos)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = philos;
	
	while (i < philos->data->number)
	{
		if (pthread_create(&tmp->threads, NULL, routine, tmp))
		{
			printf("Error:unable to create thread\n");
			return (0);
		}
		tmp = tmp->next;
		i++;
	}
	return (1);
}

int	start_t(int ac, char **av)
{
	t_philo	*philos;
	int		i;
	int		number;

	i = 0;
	philos = NULL;
	number = ft_atoi(av[1]);
	while (i < number)
	{
		if ((i + 1) == number)
			ft_lstadd_back(&philos, init_philo(i + 1, ac, av, philos));
		else
			ft_lstadd_back(&philos, init_philo(i + 1, ac, av, NULL));
		i++;
	}
	if (!creat_thread(philos))
		return (0);
	printf("         %d\n", g_all);
	return (1);
}
