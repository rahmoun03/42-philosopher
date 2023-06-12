/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:04:36 by arahmoun          #+#    #+#             */
/*   Updated: 2023/06/09 18:21:01 by arahmoun         ###   ########.fr       */
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

int	check_data(int ac, t_data *data)
{
	if ((data->number <= 0) || (data->number > 200) || (data->death < 0)
		|| (data->eat < 0) || (data->sleep < 0)
		|| (ac == 6 && data->must <= 0))
		{
			printf("Error : %sthe parameter ",YOLLOW);
			printf("is not valid %s\n", DEFFAULT);
			free(data);
			return (1);
		}
	return (0);
}

int	just_digit(char **v)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (v[i])
	{
		j = 0;
		while (v[i][j])
		{
			if ((v[i][j] < '0' || v[i][j] > '9') && j != 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
