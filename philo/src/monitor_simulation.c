/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:49:05 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/30 16:52:20 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *monitor_simulation(void *ptr)
{
    int     i;
    long    time;
    t_table	*table;

	table = (t_table *)ptr;
    while (1)
    {
        pthread_mutex_lock(&table->table_lock);
        if (table->n_of_running_threads >= table->n_of_philo)
        {
            pthread_mutex_unlock(&table->table_lock);
            break ;
        }
        pthread_mutex_unlock(&table->table_lock);
        sleep (100);
    }  

    while (!check_stop(table))
	{
        i = -1;
        while (++i < table->n_of_philo && !check_stop(table))
        {
            pthread_mutex_lock(&table->table_lock);
            if (!table->stop)
            {
                time = get_time(MILLISEC) - table->philo[i].last_meal;
                //printf("time from last meal = %ld\n", time);
                //printf("time to die = %ld\n", table->time_to_die);
                if (time > table->time_to_die)
                {
                    table->stop = true;
                    safe_printf(&table->philo[i], "died");
                }
            }
            pthread_mutex_unlock(&table->table_lock);
        }
        
	}
	return (NULL);
}