/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:53:06 by giuls             #+#    #+#             */
/*   Updated: 2024/11/03 18:21:33 by giuls            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// update header

#include "philo.h"

int	return_error_int(char *str)
{
	printf("%s\n", str);
	return (1);
}

char	*return_error_str(char *str)
{
	printf("%s\n", str);
	return (NULL);
}

void free_table(t_table *table)
{
    if (table->philo)
        free(table->philo);
    if (table->forks)
	    free(table->forks);
	free(table);
}

void	destroy_mutexes(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->n_of_philo)
    {
        pthread_mutex_destroy(&table->forks[i]);
        pthread_mutex_destroy(&table->philo[i].philo_lock);
    }
	pthread_mutex_destroy(&table->table_lock);
	pthread_mutex_destroy(&table->printf_lock);
}

int	clean_all(t_table *table, t_clean_phase clean_phase, int max)
{
    int i;

    i = -1;
	while (++i < max)
		pthread_join(table->philo[i].thread, NULL);
	if (clean_phase == MONITOR_THREAD || clean_phase == FINISHED)
		pthread_join(table->monitor_thread, NULL);
    destroy_mutexes(table);
    free_table(table);
    if (clean_phase == ROUTINE_THREAD || clean_phase == MONITOR_THREAD)
        return_error_int("pthread_create failed");
	return (0);
}
