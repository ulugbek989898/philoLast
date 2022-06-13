/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:08:30 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/13 18:18:17 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_args(int argc, char **argv, t_prog **data)
{
	(*data)->philo_nums = ft_atoi(argv[1]);
	(*data)->time_die = ft_atoi(argv[2]);
	(*data)->time_eat = ft_atoi(argv[3]);
	(*data)->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*data)->eat_nums = ft_atoi(argv[5]);
	else
		(*data)->eat_nums = 0;
}