/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 01:30:35 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/22 01:31:12 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philos *r_data, int i)
{
	ft_write_msg("has taken a fork", (*r_data).id, r_data);
	ft_write_msg("has taken a fork", (*r_data).id, r_data);
	ft_write_msg("is eating", (*r_data).id, r_data);
	pthread_mutex_lock(&(*r_data).m_struct->mutex[i]);
	r_data->last_eating_time = timestamp();
	pthread_mutex_unlock(&(*r_data).m_struct->mutex[i]);
	ft_sleep(r_data->time_eat, (*r_data).m_struct);
	pthread_mutex_lock(&(*r_data).m_struct->mutex[i]);
	(*r_data).fork = 0;
	(*r_data).philo_ate++;
	pthread_mutex_unlock(&(*r_data).m_struct->mutex[i]);
	pthread_mutex_lock(&(*r_data).m_struct->mutex[(i + 1)
		% (*r_data).ph_num]);
	(*r_data).m_struct->philos[(i + 1) % (*r_data).ph_num].fork = 0;
	pthread_mutex_unlock(&(*r_data).m_struct->mutex[(i + 1)
		% (*r_data).ph_num]);
}

void	ft_eat_sleep_think(t_philos *r_data, int i)
{
	int	died;
	int	all_ate;

	pthread_mutex_lock(&r_data->m_struct->mutex_died);
	died = r_data->m_struct->died;
	all_ate = r_data->m_struct->all_ate;
	pthread_mutex_unlock(&r_data->m_struct->mutex_died);
	if (died || all_ate)
		return ;
	ft_eat(r_data, i);
	if (died || all_ate)
		return ;
	ft_write_msg("is sleeping", (*r_data).id, r_data);
	ft_sleep(r_data->time_sleep, (*r_data).m_struct);
	ft_write_msg("is thinking", (*r_data).id, r_data);
	(*r_data).waiter = 0;
}

void	ft_create_print(t_philos *d, int i)
{
	pthread_mutex_lock(&(*d).m_struct->mutex[i]);
	pthread_mutex_lock(&(*d).m_struct->mutex[(i + 1) % (*d).ph_num]);
	if ((*d).fork == 0 && (*d).m_struct->philos[(i + 1)
			% (*d).ph_num].fork == 0 && (*d).greed != (*d).id)
	{
		(*d).fork = 2;
		(*d).greed = (*d).id;
		(*d).m_struct->philos[(i + 1) % (*d).ph_num].fork = 2;
		(*d).m_struct->philos[(i + 1) % (*d).ph_num].greed = (*d).id;
		(*d).waiter = 1;
		pthread_mutex_unlock(&(*d).m_struct->mutex[i]);
		pthread_mutex_unlock(&(*d).m_struct->mutex[(i + 1) % (*d).ph_num]);
	}
	else
	{
		pthread_mutex_unlock(&(*d).m_struct->mutex[i]);
		pthread_mutex_unlock(&(*d).m_struct->mutex[(i + 1) % (*d).ph_num]);
	}
	if ((*d).waiter)
		ft_eat_sleep_think(d, i);
}

void	*routine(void *data)
{
	t_philos	*r_data;
	int			i;
	int			d;
	int			all_ate;

	i = 0;
	r_data = (t_philos *)data;
	while (1)
	{
		pthread_mutex_lock(&(r_data->m_struct->mutex_died));
		d = r_data->m_struct->died;
		all_ate = r_data->m_struct->all_ate;
		pthread_mutex_unlock(&(r_data->m_struct->mutex_died));
		if (d || all_ate)
			break ;
		ft_create_print(r_data, (*r_data).id);
		usleep(100);
		i++;
	}
	return (NULL);
}
