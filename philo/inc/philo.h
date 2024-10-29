/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:32:44 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/29 13:07:54 by mpellegr         ###   ########.fr       */
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

typedef enum e_thread_operation
{
	INIT,
	CREATE,
	LOCK,
	UNLOCK,
	JOIN,
	DESTROY
}	t_thread_operation;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
	int				n_of_meals;
//	long long int	last_meal;
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
	pthread_mutex_t	lock_action;
	long			start;
}	t_table;

void	*routine(void *ptr);
int		create_table(char **argv, t_table *table);
long	get_time();

int		return_error_int(char *str);
char	*return_error_str(char *str);

#endif