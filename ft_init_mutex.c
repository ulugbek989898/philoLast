/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:23:30 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/19 14:04:56 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_mutex(t_prog **data)
{
	int	i;

	i = 0;
	while (i < (*data)->philo_nums)
	{
		pthread_mutex_init(&(*data)->mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&(*data)->main_mutex, NULL);
	pthread_mutex_init(&(*data)->mutex_died, NULL);
	pthread_mutex_init(&(*data)->meal_check, NULL);
}

void	ft_destroy_mutex(t_prog **data)
{
	int	i;

	i = 0;
	while (i < (*data)->philo_nums)
	{
		pthread_mutex_destroy(&(*data)->mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&(*data)->main_mutex);
	pthread_mutex_destroy(&(*data)->mutex_died);
	pthread_mutex_destroy(&(*data)->meal_check);
}
