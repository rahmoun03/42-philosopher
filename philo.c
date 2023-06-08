/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:04:36 by arahmoun          #+#    #+#             */
/*   Updated: 2023/06/08 10:15:24 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(char **av, int ac)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->number = ft_atoi(av[1]);
	data->death = ft_atoi(av[2]);
	data->eat = ft_atoi(av[3]);
	data->sleep = ft_atoi(av[4]);
	printf("number = %d\ndie    = %d\neat    = %d\nsleep  = %d\n", data->number,
		data->death, data->eat, data->sleep);
	if (ac == 6)
	{
		data->must = ft_atoi(av[5]);
		printf("must   = %d\n", data->must);
	}
	else
		data->must = -1;
	printf("%s                       %s\n", GREEN, DEFFAULT);
	return (data);
}

int	check_data(int ac, char **av)
{
	t_data	*data;

	data = init_data(av, ac);
	if (data->number <= 0 || data->number > 200 || data->death < 0
		|| data->eat < 0 || data->sleep < 0)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (!check_data(ac, av))
		{
			printf("Error\n");
			return (1);
		}
		start_t(ac, av);
	}
	else
		printf("Error : you must at lest enter 5 argument\n");
}
