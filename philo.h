/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:47:55 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/13 18:15:22 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_prog
{
	int	philo_nums;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	time_sleep;
	int	eat_nums;
}	t_prog;

int		ft_atoi(const char *str);
int		check_arguments(int argc, char **argv);
void	ft_init_args(int argc, char **argv, t_prog **data);

#endif