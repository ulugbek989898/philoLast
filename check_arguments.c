/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 12:18:41 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/22 04:30:38 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
			i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			i++;
			continue ;
		}
		return (1);
	}
	return (0);
}

int	ft_optional_arg(char **argv)
{
	int	num_of_eating;

	num_of_eating = 0;
	if (ft_isdigit(argv[5]))
	{
		write(2, "Optional num are not good! Try again.\n", 38);
		return (1);
	}
	num_of_eating = ft_atoi(argv[5]);
	if (!(num_of_eating > 0))
	{
		write(2, "Num of eating is not proper value. Try again.\n", 46);
		return (1);
	}
	return (0);
}

int	check_arguments(int argc, char **argv)
{
	int	num_of_philos;

	num_of_philos = ft_atoi(argv[1]);
	if (!(num_of_philos > 0 && num_of_philos <= 200) || ft_isdigit(argv[1]))
	{
		write(2, "Philos num are not good! Try again.\n", 36);
		return (1);
	}
	if (ft_isdigit(argv[2]) || ft_isdigit(argv[3]) || ft_isdigit(argv[4]))
	{
		write(2, "Given Time is not proper value. Try again.\n", 44);
		return (1);
	}
	if (!(ft_atoi(argv[2]) >= 60 && ft_atoi(argv[3]) >= 60
			&& ft_atoi(argv[4]) >= 60))
	{
		write(2, "Given Time is not proper value. Try again.\n", 44);
		return (1);
	}
	if (argc == 6)
		if (ft_optional_arg(argv))
			return (1);
	return (0);
}
