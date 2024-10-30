/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:19:28 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/30 16:55:07 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    wait_all_threads_to_be_created(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->table_lock);
	while (!philo->table->all_threads_created)
	{
        pthread_mutex_unlock(&philo->table->table_lock);
        usleep(100);
        pthread_mutex_lock(&philo->table->table_lock);
    }
	pthread_mutex_unlock(&philo->table->table_lock);
}
