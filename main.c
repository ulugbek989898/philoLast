/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:49:02 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/18 18:53:53 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write_msg(char *str, int id, t_philos *r_data)
{
	if (!r_data->main_struct->died)
	{
		pthread_mutex_lock(&r_data->main_struct->main_mutex);
		printf("%lld ", timestamp() - r_data->main_struct->init_time);
		printf("%d %s\n", id + 1, str);
		pthread_mutex_unlock(&r_data->main_struct->main_mutex);
	}
}

void	ft_create_print(t_philos *r_data, int i)
{
	int	waiter;

	pthread_mutex_lock(&(*r_data).main_struct->main_mutex);
	waiter = 0;
	pthread_mutex_unlock(&(*r_data).main_struct->main_mutex);
	pthread_mutex_lock(&(*r_data).main_struct->mutex[i]);
	if ((*r_data).fork == 0)
	{
		pthread_mutex_lock(&(*r_data).main_struct->mutex[(i + 1) % (*r_data).philo_nums]);
		if ((*r_data).main_struct->philos[(i + 1) % (*r_data).philo_nums].fork == 0)
		{
			(*r_data).fork = 2;
			(*r_data).main_struct->philos[(i + 1) % (*r_data).philo_nums].fork = 2;
			pthread_mutex_unlock(&(*r_data).main_struct->mutex[(i + 1) % (*r_data).philo_nums]);
			pthread_mutex_unlock(&(*r_data).main_struct->mutex[i]);
			pthread_mutex_lock(&(*r_data).main_struct->main_mutex);
			waiter = 1;
			pthread_mutex_unlock(&(*r_data).main_struct->main_mutex);
		}
		else
		{
			pthread_mutex_unlock(&(*r_data).main_struct->mutex[(i + 1) % (*r_data).philo_nums]);
			pthread_mutex_unlock(&(*r_data).main_struct->mutex[i]);
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

void	*print(void *data)
{
	t_philos	*r_data;
	int			i;

	i = 0;
	r_data = (t_philos *)data;
	while (!(*r_data).main_struct->died)
	{
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
		if (pthread_create(&(*data)->threads[i], NULL, &print, &(*data)->philos[i]))
			perror("Creating pthread failed");
		// pthread_mutex_lock(&(*data)->mutex[i]);
		(*data)->philos[i].last_eating_time = timestamp();
		// pthread_mutex_unlock(&(*data)->mutex[i]);
		i++;
	}
}

void	ft_death_check(t_prog **data)
{
	int	i;

	i = 0;
	while (!(*data)->died)
	{
		i=0;
		while (i < (*data)->philo_nums)
		{
			pthread_mutex_lock(&((*data)->meal_check));
			if (time_diff((*data)->philos[i].last_eating_time, timestamp()) > (*data)->philos[i].time_die)
			{
				ft_write_msg("is died", i, &(*data)->philos[i]);
				(*data)->died = 1;
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
	ft_destroy_mutex(&data);
	ft_create_join(&data);
}
