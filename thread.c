/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:30:53 by arahmoun          #+#    #+#             */
/*   Updated: 2023/06/07 12:29:21 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*PrintHello(void *philos)
{
	t_philo *tmp;

	tmp = (t_philo *)philos;
	printf("creating thread, %d\n", tmp->id);
	for (int i = 0; i < 4; i++)
	{
		printf("philo %d is working %d time\n", tmp->id, i + 1);
	}
	return(philos);
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

t_philo	*init_philo(int id, int ac, char **av, t_philo *last){
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo));
	philos->data = (t_data *)malloc(sizeof(t_data));
	philos->id = id;
	pthread_mutex_init(&philos->fork, NULL);
	philos->data->number = ft_atoi(av[1]);
	philos->data->death = ft_atoi(av[2]);
	philos->data->eat = ft_atoi(av[3]);
	philos->data->sleep = ft_atoi(av[4]);
	if(ac == 6)
		philos->data->must = ft_atoi(av[5]);
	else
		philos->data->must = -1;
	pthread_mutex_init(&philos->data->mutex, NULL);
	philos->next = last;
	return (philos);
}

int	creat_thread(t_philo *philos){
	int i;
	t_philo *tmp;

	i = 0;
	tmp = philos;
	while (i < philos->data->number)
	{
		if(pthread_create(&philos->threads, NULL, PrintHello, tmp))
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
	t_philo *philos;
	int i;
	int number;

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
	return (1);
}
