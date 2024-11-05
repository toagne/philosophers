/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:32:44 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/05 12:58:15 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef enum e_time_option
{
	MILLISEC,
	MICROSEC
}	t_time_option;

typedef enum e_clean_phase
{
	ROUTINE_THREAD,
	MONITOR_THREAD,
	FINISHED
}	t_clean_phase;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	long			n_of_meals;
	long			last_meal;
	long			is_full;
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
	long			all_threads_created;
	long			stop;
	long			start;
	long			n_of_running_threads;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	table_lock;
	pthread_mutex_t	printf_lock;
	pthread_t		monitor_thread;
}	t_table;

int		create_table(char **argv, t_table *table);

int		init_data(t_table *table);

void	*routine(void *ptr);
void	*monitor_routine(void *ptr);

long	get_time(t_time_option time_option);
int		check_stop(t_table *table);
void	ft_usleep(long input_time, t_table *table);
void	safe_printf(t_philo *philo, char *str);
void	destroy_mutex_array(pthread_mutex_t *mutex, t_table *table);

int		return_error_int(char *str);
char	*return_error_str(char *str);
void	free_table(t_table *table);
int		clean_all(t_table *table, t_clean_phase clean_phase, int i);
void	destroy_mutexes(t_table *table);

void	wait_all_threads_to_be_created(t_philo *philo);
void	wait_all_threads_to_run(t_table *table);

void	safe_set_long(pthread_mutex_t *mutex, long *var, long value);
long	safe_get_long(pthread_mutex_t *mutex, long var);
void	safe_increase_long(pthread_mutex_t *mutex, long *var);

#endif