/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:49:02 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/22 01:34:33 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_thread(t_prog **data)
{
	int	i;

	i = 0;
	(*data)->init_time = timestamp();
	while (i < (*data)->ph_num)
	{
		if (pthread_create(&(*data)->threads[i], NULL,
				&routine, &(*data)->philos[i]))
			perror("Creating pthread failed");
		pthread_mutex_lock(&(*data)->mutex[i]);
		(*data)->philos[i].last_eating_time = timestamp();
		pthread_mutex_unlock(&(*data)->mutex[i]);
		usleep(50);
		i++;
	}
}

int	ft_rep_check_death(int i, t_prog **data)
{
	long long	l_e_time;

	pthread_mutex_lock(&(*data)->mutex[i]);
	l_e_time = (*data)->philos[i].last_eating_time;
	pthread_mutex_unlock(&(*data)->mutex[i]);
	if (time_diff(l_e_time, timestamp()) >= (*data)->philos[i].time_die)
	{
		pthread_mutex_lock(&((*data)->mutex_died));
		(*data)->died = 1;
		pthread_mutex_unlock(&((*data)->mutex_died));
		ft_write_msg1("is died", i, &(*data)->philos[i]);
		return (1);
	}
	return (0);
}

void	ft_death_check(t_prog **data)
{
	int			i;
	int			d;

	while (!((*data)->all_ate))
	{
		i = 0;
		while (i < (*data)->ph_num)
		{
			if (ft_rep_check_death(i, data))
				break ;
			usleep(100);
			i++;
		}
		pthread_mutex_lock(&(*data)->mutex_died);
		d = (*data)->died;
		pthread_mutex_unlock(&(*data)->mutex_died);
		if (d)
			break ;
		i = 0;
		while ((*data)->philos[i].meal_nums && i < (*data)->ph_num
			&& (*data)->philos[i].philo_ate >= (*data)->philos[i].meal_nums)
			i++;
		if (i == (*data)->ph_num)
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
