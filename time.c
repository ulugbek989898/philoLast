/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 20:47:43 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/22 01:35:12 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	ft_sleep(long long time, t_prog *data)
{
	long long	i;
	int			d;

	i = timestamp();
	while (1)
	{
		pthread_mutex_lock(&(data)->mutex_died);
		d = data->died;
		pthread_mutex_unlock(&(data)->mutex_died);
		if (d)
			break ;
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(100);
	}
}
