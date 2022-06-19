/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:49:02 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/19 17:08:40 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_print(t_philos *r_data, int i)
{
	int	waiter;

	pthread_mutex_lock(&(*r_data).main_struct->main_mutex);
	waiter = 0;
	pthread_mutex_unlock(&(*r_data).main_struct->main_mutex);
	pthread_mutex_lock(&(*r_data).main_struct->mutex[i]);
	if ((*r_data).fork == 0 && (*r_data).greed != (*r_data).id)
	{
		pthread_mutex_lock(&(*r_data).main_struct->mutex[(i + 1) % (*r_data).philo_nums]);
		if ((*r_data).main_struct->philos[(i + 1) % (*r_data).philo_nums].fork == 0)
		{
			(*r_data).fork = 2;
			(*r_data).greed = (*r_data).id;
			(*r_data).main_struct->philos[(i + 1) % (*r_data).philo_nums].fork = 2;
			(*r_data).main_struct->philos[(i + 1) % (*r_data).philo_nums].greed = (*r_data).id;
			pthread_mutex_unlock(&(*r_data).main_struct->mutex[i]);
			pthread_mutex_unlock(&(*r_data).main_struct->mutex[(i + 1) % (*r_data).philo_nums]);
			pthread_mutex_lock(&(*r_data).main_struct->main_mutex);
			waiter = 1;
			pthread_mutex_unlock(&(*r_data).main_struct->main_mutex);
		}
		else
		{
			pthread_mutex_unlock(&(*r_data).main_struct->mutex[i]);
			pthread_mutex_unlock(&(*r_data).main_struct->mutex[(i + 1) % (*r_data).philo_nums]);
			usleep(100);
		}
	}
	else
		pthread_mutex_unlock(&(*r_data).main_struct->mutex[i]);
	if (waiter)
	{
		ft_write_msg("has taken a fork", (*r_data).id, r_data);
		ft_write_msg("has taken a fork", (*r_data).id, r_data);
		ft_write_msg("is eating", (*r_data).id, r_data);
		pthread_mutex_lock(&(*r_data).main_struct->mutex[i]);
		r_data->last_eating_time = timestamp();
		pthread_mutex_unlock(&(*r_data).main_struct->mutex[i]);
		ft_sleep(r_data->time_eat, (*r_data).main_struct);
		pthread_mutex_lock(&(*r_data).main_struct->mutex[i]);
		(*r_data).fork = 0;
		pthread_mutex_unlock(&(*r_data).main_struct->mutex[i]);
		pthread_mutex_lock(&(*r_data).main_struct->mutex[(i + 1) % (*r_data).philo_nums]);
		(*r_data).main_struct->philos[(i + 1) % (*r_data).philo_nums].fork = 0;
		pthread_mutex_unlock(&(*r_data).main_struct->mutex[(i + 1) % (*r_data).philo_nums]);
		ft_write_msg("is sleeping", (*r_data).id, r_data);
		ft_sleep(r_data->time_sleep, (*r_data).main_struct);
		ft_write_msg("is thinking", (*r_data).id, r_data);
	}
}

void	*routine(void *data)
{
	t_philos	*r_data;
	int			i;
	int			d;
	i = 0;
	r_data = (t_philos *)data;
	while (1)
	{
		pthread_mutex_lock(&(r_data->main_struct->mutex_died));
		d = r_data->main_struct->died;
		pthread_mutex_unlock(&(r_data->main_struct->mutex_died));
		if (d)
			break ;
		ft_create_print(r_data, (*r_data).id);
		i++;
	}
	return (NULL);
}

void	ft_create_thread(t_prog **data)
{
	int	i;

	i = 0;
	(*data)->init_time = timestamp();
	while (i < (*data)->philo_nums)
	{
		if (pthread_create(&(*data)->threads[i], NULL, &routine, &(*data)->philos[i]))
			perror("Creating pthread failed");
		pthread_mutex_lock(&(*data)->mutex[i]);
		(*data)->philos[i].last_eating_time = timestamp();
		pthread_mutex_unlock(&(*data)->mutex[i]);
		i++;
	}
}

void	ft_death_check(t_prog **data)
{
	int	i;
	int	d;
	long long	last_ate_time;
	
	while (1)
	{
		i=0;
		pthread_mutex_lock(&(*data)->mutex_died);
		d = (*data)->died;
		pthread_mutex_unlock(&(*data)->mutex_died);
		if (d)
			break ;
		while (i < (*data)->philo_nums)
		{
			pthread_mutex_lock(&(*data)->mutex[i]);
			last_ate_time = (*data)->philos[i].last_eating_time;
			pthread_mutex_unlock(&(*data)->mutex[i]);
			pthread_mutex_lock(&((*data)->meal_check));
			if (time_diff(last_ate_time, timestamp()) > (*data)->philos[i].time_die)
			{
				ft_write_msg("is died", i, &(*data)->philos[i]);
				pthread_mutex_lock(&((*data)->mutex_died));
				(*data)->died = 1;
				pthread_mutex_unlock(&((*data)->mutex_died));
				usleep(100);
			}
			pthread_mutex_unlock(&((*data)->meal_check));
			usleep(100);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_prog	*data;

	data = NULL;
	if (!(argc == 5 || argc == 6))
	{
		write(2, "Wrong arguments\n", 16);
		return (0);
	}
	if (check_arguments(argc, argv))
		return (1);
	data = malloc(sizeof(t_prog));
	ft_init_args(argc, argv, &data);
	ft_init_mutex(&data);
	ft_create_thread(&data);
	ft_death_check(&data);
	ft_create_join(&data);
	ft_destroy_mutex(&data);
}
