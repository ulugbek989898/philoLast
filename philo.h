/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:47:55 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/15 18:06:02 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_prog
{
	int				philo_nums;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eat_nums;
	pthread_mutex_t	mutex[200];
	pthread_t		threads[200];
	int				forks[200];
}	t_prog;

int		ft_atoi(const char *str);
int		check_arguments(int argc, char **argv);
void	ft_init_args(int argc, char **argv, t_prog **data);
void	ft_init_mutex(t_prog **data);
void	ft_destroy_mutex(t_prog **data);
void	ft_create_join(t_prog **data);
#endif