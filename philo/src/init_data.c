/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:40:08 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/30 16:52:11 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void init_forks(t_table *table, int i)
{
    if (table->philo[i].id % 2 == 0)
    {
        table->philo[i].first_fork = &table->forks[i];
        table->philo[i].second_fork = &table->forks[(i + 1) % table->n_of_philo];
    }
    else
    {
        table->philo[i].first_fork = &table->forks[(i + 1) % table->n_of_philo];
        table->philo[i].second_fork = &table->forks[i];
    }
    
}

static void philo_init(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->n_of_philo)
    {
        table->philo[i].id = i + 1;
        table->philo[i].n_of_meals = 0;
        table->philo[i].table = table;
        table->philo[i].is_full = false;
        pthread_mutex_init(&table->philo[i].philo_lock, NULL); //check if it fails
        init_forks(table, i);
    }
}

int init_data(t_table *table)
{
    int i;

    i = -1;
    table->philo = malloc(sizeof(t_philo) * table->n_of_philo);
    if (!table->philo)
        return (return_error_int("malloc failed"));
    table->forks = malloc(sizeof(pthread_mutex_t) * table->n_of_philo);
    if (!table->forks)
    {
        free(table->philo);
        return (return_error_int("malloc failed"));
    }
    while (++i < table->n_of_philo)
    {
        if (pthread_mutex_init(&table->forks[i], NULL)) //destroy + clean
            return (return_error_int("mutex init failed"));
    }
    if (pthread_mutex_init(&table->table_lock, NULL)) //destroy + clean
        return (return_error_int("mutex init failed"));
    if (pthread_mutex_init(&table->printf_lock, NULL)) //destroy + clean
        return (return_error_int("mutex init failed"));
    table->all_threads_created = false;
    table->stop = false;
    table->n_of_running_threads = 0;
    philo_init(table);
    return (0);
}