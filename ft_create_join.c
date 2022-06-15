/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:44:58 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/15 18:05:48 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_join(t_prog **data)
{
	int	i;

	i = 0;
	while (i < (*data)->philo_nums)
	{
		pthread_join((*data)->threads[i], NULL);
		i++;
	}
}