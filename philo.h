/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:47:55 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/18 17:26:16 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philos
{
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				philo_nums;
	int				id;
	long long		last_eating_time;
	int				fork;
	struct s_prog	*main_struct;
}	t_philos;

typedef struct s_prog
{
	int				philo_nums;
	int				eat_nums;
	int				died;
	int				count;
	long long		init_time;
	pthread_mutex_t	mutex[200];
	pthread_mutex_t	main_mutex;
	pthread_mutex_t	meal_check;
	pthread_t		threads[200];
	t_philos		philos[200];
}	t_prog;

int			ft_atoi(const char *str);
int			check_arguments(int argc, char **argv);
void		ft_init_args(int argc, char **argv, t_prog **data);
void		ft_init_mutex(t_prog **data);
void		ft_destroy_mutex(t_prog **data);
void		ft_create_join(t_prog **data);
long long	time_diff(long long past, long long pres);
void		ft_sleep(long long time, t_prog *data);
long long	timestamp(void);
#endif