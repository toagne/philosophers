/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:32:44 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/30 16:53:09 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>

typedef enum e_time_option
{
	SEC,
	MILLISEC,
	MICROSEC
}	t_time_option;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				n_of_meals;
	long			last_meal;
	bool			is_full;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	struct s_table	*table;
	pthread_mutex_t	philo_lock;
}	t_philo;

typedef struct s_table
{
	int				n_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_times_to_eat;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	bool			all_threads_created;
	bool			stop;
	pthread_mutex_t	table_lock;
	long			start;
	pthread_t		monitor_thread;
	int				n_of_running_threads;
	pthread_mutex_t	printf_lock;
}	t_table;

int		create_table(char **argv, t_table *table);

int 	init_data(t_table *table);

void	*routine(void *ptr);
void    *monitor_simulation(void *ptr);

long	get_time();
int		check_stop(t_table *table);
void    ft_usleep(long input_time, t_philo *philo);
void	safe_printf(t_philo *philo, char *str);

int		return_error_int(char *str);
char	*return_error_str(char *str);

void    wait_all_threads_to_be_created(t_philo *philo);

#endif