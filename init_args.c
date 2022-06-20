/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:08:30 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/20 19:57:01 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_args(int argc, char **argv, t_prog **data)
{
	int	i;

	(*data)->philo_nums = ft_atoi(argv[1]);
	
	if (argc == 6)
		(*data)->eat_nums = ft_atoi(argv[5]);
	else
		(*data)->eat_nums = 0;
	i = 0;
	while (i < (*data)->philo_nums)
	{
		(*data)->philos[i].philo_nums = ft_atoi(argv[1]);
		(*data)->philos[i].time_die = ft_atoi(argv[2]);
		(*data)->philos[i].time_eat = ft_atoi(argv[3]);
		(*data)->philos[i].time_sleep = ft_atoi(argv[4]);
		(*data)->philos[i].id = i;
		(*data)->philos[i].main_struct = *data;
		(*data)->philos[i].fork = 0;
		(*data)->philos[i].greed = 10000;
		(*data)->philos[i].philo_ate = 0;
		(*data)->philos[i].waiter = 0;
		(*data)->philos[i].meal_nums = (*data)->eat_nums;
		i++;
	}
	(*data)->died = 0;
	(*data)->count = 0;
	(*data)->all_ate = 0;
}
