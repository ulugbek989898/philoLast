/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:41:18 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/19 14:18:41 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		if (n < 0)
		{
			ft_putchar('-');
			ft_putnbr(-n);
		}
		else if (n > 9)
		{
			ft_putnbr(n / 10);
			ft_putchar(n % 10 + '0');
		}
		else
			ft_putchar(n + '0');
	}
}

void	ft_write_msg(char *str, int id, t_philos *r_data)
{
	int d;
	
	pthread_mutex_lock(&(*r_data).main_struct->mutex_died);
	d = r_data->main_struct->died;
	pthread_mutex_unlock(&(*r_data).main_struct->mutex_died);
	if (!d)
	{
		pthread_mutex_lock(&r_data->main_struct->main_mutex);
		ft_putnbr(timestamp() - r_data->main_struct->init_time);
		ft_putchar(' ');
		ft_putnbr(id + 1);
		ft_putchar(' ');
		ft_putstr(str);
		ft_putchar('\n');
		pthread_mutex_unlock(&r_data->main_struct->main_mutex);
	}
}