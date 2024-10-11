/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:32:44 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/11 10:37:07 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
	int				n_of_meals;
	long long int	last_meal;
}	t_philo;

typedef struct s_table
{
	int				n_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_times_to_eat;
	long long int	start;
	t_philo			*philo;
	pthread_mutex_t	lock_action;
	pthread_mutex_t	*forks;
}	t_table;

void			*routine(void *ptr);
void			create_table(char **argv, t_table *table);
long long int	get_time();

#endif