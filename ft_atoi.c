/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:19:42 by arahmoun          #+#    #+#             */
/*   Updated: 2023/04/29 13:47:33 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	ft_error(void)
{
	printf("%sError%s\n", RED, DEFFAULT);
	exit(1);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static	void	ft_sing(char c, int *sing, int *i)
{
	if (c == '-' || c == '+')
	{
		if (c == '-')
			*sing = *sing * (-1);
		*i = *i + 1;
	}
}

static	void	ft_skip_spaces(const char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\n' || str[*i] == '\t'
		|| '\v' == str[*i] || str[*i] == '\r' || str[*i] == '\f')
		*i = *i + 1;
}

static	void	check_error(const char *str, int i)
{
	if ((str[i] != '\0' && (str[i] > '9' || str[i] < '0') && str[i] != ' ')
		|| (ft_strlen(str) == 0))
		ft_error();
	else if ((str[i] == '-') || (str[i] == '+'))
		ft_error();
	else if ((str[i] == '\0' || str[i] == ' ')
		&& (str[i - 1] == '-' || str[i - 1] == '+'))
		ft_error();
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sing;
	unsigned long	val;

	sing = 1;
	i = 0;
	val = 0;
	ft_skip_spaces(str, &i);
	ft_sing(str[i], &sing, &i);
	while (str[i] <= '9' && str[i] >= '0' && str[i])
	{
		val = val * 10 + (str[i] - 48);
		if ((val > 2147483647 && sing == 1) || (val > 2147483648 && sing == -1))
			ft_error();
		i++;
	}
	check_error(str, i);
	return (val * sing);
}
