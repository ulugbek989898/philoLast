/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:49:02 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/15 18:15:54 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*print(void *data)
{
	t_prog	*r_data;

	r_data = (t_prog *)data;
	r_data->time_eat = r_data->time_eat + 150;
	printf("philo num is %d\n", r_data->time_eat);
	return (NULL);
}

void	ft_create_thread(t_prog **data)
{
	int	i;

	i = 0;
	while (i < (*data)->philo_nums)
	{
		pthread_create(&(*data)->threads[i], NULL, &print, *data);
		i++;
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
	ft_create_join(&data);
	ft_destroy_mutex(&data);
	printf("philo num is %d\n", data->time_eat);
}
