/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 12:23:11 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/12 20:35:14 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_return(unsigned int result, int sign)
{
	if (result > 2147483647 && sign == 1)
		return (0);
	if (result > 2147483648 && sign == -1)
		return (0);
	return (sign * result);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned int	result;
	unsigned int	res;

	sign = 1;
	result = 0;
	res = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = result;
		result = result * 10 + str[i++] - '0';
		if (res > result)
			return (0);
	}
	return (ft_return(result, sign));
}
