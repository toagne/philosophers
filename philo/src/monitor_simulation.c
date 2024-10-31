/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:49:05 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/31 18:01:44 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stop(t_table *table)
{
    pthread_mutex_lock(&table->table_lock);
	if (table->stop)
    {
        pthread_mutex_unlock(&table->table_lock);
        return (1);
    }
	pthread_mutex_unlock(&table->table_lock);
	return (0);
}
void    *monitor_simulation(void *ptr)
{
    int     i;
    long    time;
    t_table	*table;
    int     full_count;

	table = (t_table *)ptr;
    wait_all_threads_to_be_created_for_monitor(table);
    while (1)
	{
        if (check_stop(table))
            break ;
        full_count = 0;
        i = -1;
        while (++i < table->n_of_philo)
        {
            pthread_mutex_lock(&table->table_lock);
            if (!table->stop)
            {
                time = get_time(MILLISEC) - table->start;                
                if (time - table->philo[i].last_meal > table->time_to_die)
                {
                    safe_printf(&table->philo[i], "died");
                    table->stop = 1;
                    pthread_mutex_unlock(&table->table_lock);
                    break ;
                }
            }
            pthread_mutex_unlock(&table->table_lock);
            if (table->n_of_times_to_eat != -1)
            {
                pthread_mutex_lock(&table->philo[i].philo_lock);
                if (table->philo[i].is_full == 1)
                    full_count++;
                pthread_mutex_unlock(&table->philo[i].philo_lock);
            }
        }
        if (table->n_of_times_to_eat != -1 && full_count == table->n_of_philo)
        {
            safe_set_long(&table->table_lock, &table->stop, 1);
            break;
        }
        usleep(100);
    }
	return (NULL);
}