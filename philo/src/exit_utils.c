/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:22:13 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/08 16:45:59 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	free_table(t_table *table)
{
	if (table->philo)
		free(table->philo);
	if (table->forks)
		free(table->forks);
	free(table);
}

void	destroy_mutexes(t_table *table)
{
	int	i;

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
	int	i;

	i = -1;
	if (max == 0)
		max = 1;
	while (++i < max)
		pthread_join(table->philo[i].thread, NULL);
	if (clean_phase == MONITOR_THREAD || clean_phase == FINISHED)
		pthread_join(table->monitor_thread, NULL);
	destroy_mutexes(table);
	free_table(table);
	if (clean_phase == ROUTINE_THREAD || clean_phase == MONITOR_THREAD)
		return (return_error_int("pthread_create failed"));
	return (0);
}
