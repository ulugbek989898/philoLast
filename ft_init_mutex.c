/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:23:30 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/15 16:41:55 by uisroilo         ###   ########.fr       */
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
}
