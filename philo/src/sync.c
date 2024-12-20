/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:19:28 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/04 10:17:41 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads_to_be_created(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->table->table_lock);
		if (philo->table->all_threads_created)
		{
			pthread_mutex_unlock(&philo->table->table_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->table_lock);
		usleep(100);
	}
}

void	wait_all_threads_to_run(t_table *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->table_lock);
		if (table->n_of_running_threads >= table->n_of_philo)
		{
			pthread_mutex_unlock(&table->table_lock);
			break ;
		}
		pthread_mutex_unlock(&table->table_lock);
		usleep(100);
	}
}
