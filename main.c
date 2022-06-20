/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:49:02 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/20 20:10:50 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_print(t_philos *r_data, int i)
{
	if (r_data->main_struct->died)
		return ;
	pthread_mutex_lock(&(*r_data).main_struct->mutex[i]);
	pthread_mutex_lock(&(*r_data).main_struct->mutex[(i + 1) % (*r_data).philo_nums]);
	if ((*r_data).fork == 0 && (*r_data).main_struct->philos[(i + 1) % (*r_data).philo_nums].fork == 0 && (*r_data).greed != (*r_data).id)
	{
		(*r_data).fork = 2;
		(*r_data).greed = (*r_data).id;
		(*r_data).main_struct->philos[(i + 1) % (*r_data).philo_nums].fork = 2;
		(*r_data).main_struct->philos[(i + 1) % (*r_data).philo_nums].greed = (*r_data).id;
		(*r_data).waiter = 1;
		pthread_mutex_unlock(&(*r_data).main_struct->mutex[i]);
		pthread_mutex_unlock(&(*r_data).main_struct->mutex[(i + 1) % (*r_data).philo_nums]);
	}
	else
	{
		pthread_mutex_unlock(&(*r_data).main_struct->mutex[i]);
		pthread_mutex_unlock(&(*r_data).main_struct->mutex[(i + 1) % (*r_data).philo_nums]);
	}
	if ((*r_data).waiter)
	{
		if (r_data->main_struct->died)
			return ;
		ft_write_msg("has taken a fork", (*r_data).id, r_data);
		ft_write_msg("has taken a fork", (*r_data).id, r_data);
		ft_write_msg("is eating", (*r_data).id, r_data);
		pthread_mutex_lock(&(*r_data).main_struct->mutex[i]);
		r_data->last_eating_time = timestamp();
		pthread_mutex_unlock(&(*r_data).main_struct->mutex[i]);
		ft_sleep(r_data->time_eat, (*r_data).main_struct);
		pthread_mutex_lock(&(*r_data).main_struct->mutex[i]);
		(*r_data).fork = 0;
		(*r_data).philo_ate++;
		pthread_mutex_unlock(&(*r_data).main_struct->mutex[i]);
		pthread_mutex_lock(&(*r_data).main_struct->mutex[(i + 1) % (*r_data).philo_nums]);
		(*r_data).main_struct->philos[(i + 1) % (*r_data).philo_nums].fork = 0;
		pthread_mutex_unlock(&(*r_data).main_struct->mutex[(i + 1) % (*r_data).philo_nums]);
		if (r_data->main_struct->died)
			return ;
		ft_write_msg("is sleeping", (*r_data).id, r_data);
		ft_sleep(r_data->time_sleep, (*r_data).main_struct);
		ft_write_msg("is thinking", (*r_data).id, r_data);
		if (r_data->main_struct->died)
			return ;
		(*r_data).waiter = 0;
	}
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
		pthread_mutex_lock(&(r_data->main_struct->mutex_died));
		d = r_data->main_struct->died;
		all_ate = r_data->main_struct->all_ate;
		if (d || all_ate)
		{
			pthread_mutex_unlock(&(r_data->main_struct->mutex_died));
			break ;
		}
		pthread_mutex_unlock(&(r_data->main_struct->mutex_died));
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
		usleep(50);
		i++;
	}
}

void	ft_death_check(t_prog **data)
{
	int	i;
	int	d;
	long long	last_ate_time;
	
	while (!((*data)->all_ate))
	{
		i=0;
		while (i < (*data)->philo_nums)
		{
			// pthread_mutex_lock(&(*data)->mutex[i]);
			last_ate_time = (*data)->philos[i].last_eating_time;
			// pthread_mutex_unlock(&(*data)->mutex[i]);
			// pthread_mutex_lock(&((*data)->meal_check));
			if (time_diff(last_ate_time, timestamp()) >= (*data)->philos[i].time_die)
			{
				pthread_mutex_lock(&((*data)->mutex_died));
				(*data)->died = 1;
				pthread_mutex_unlock(&((*data)->mutex_died));
				// usleep(100);
				ft_write_msg1("is died", i, &(*data)->philos[i]);
				break ;
			}
			// pthread_mutex_unlock(&((*data)->meal_check));
			// usleep(100);
			i++;
		}
		pthread_mutex_lock(&(*data)->mutex_died);
		d = (*data)->died;
		pthread_mutex_unlock(&(*data)->mutex_died);
		if (d)
			break ;
		i = 0;
		while ((*data)->philos[i].meal_nums && i < (*data)->philo_nums && (*data)->philos[i].philo_ate >= (*data)->philos[i].meal_nums)
			i++;
		if (i == (*data)->philo_nums)
			(*data)->all_ate = 1;
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
