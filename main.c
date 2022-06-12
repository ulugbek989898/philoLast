/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:49:02 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/12 22:39:22 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
	{
		write(2, "Wrong arguments\n", 16);
		return (0);
	}
	if (check_arguments(argc, argv))
		return (1);
	
}
