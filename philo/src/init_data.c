/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:40:08 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/31 15:49:53 by mpellegr         ###   ########.fr       */
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

static int philo_init(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->n_of_philo)
    {
        table->philo[i].id = i + 1;
        table->philo[i].n_of_meals = 0;
        table->philo[i].table = table;
        table->philo[i].is_full = 0;
        //table->philo[i].last_meal = get_time();
        init_forks(table, i);
        //table->philo[i].first_fork = &table->forks[i];
        //table->philo[i].second_fork = &table->forks[(i + 1) % table->n_of_philo];
        if (pthread_mutex_init(&table->philo[i].philo_lock, NULL) != 0)
            return (return_error_int("mutex init failed"));
    }
    return (0);
}

static int  init_mutexes(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->n_of_philo)
    {
        if (pthread_mutex_init(&table->forks[i], NULL)) //destroy + clean
            return (return_error_int("mutex init failed"));
    }
    if (pthread_mutex_init(&table->table_lock, NULL)) //destroy + clean
        return (return_error_int("mutex init failed"));
    if (pthread_mutex_init(&table->printf_lock, NULL)) //destroy + clean
        return (return_error_int("mutex init failed"));
    return (0);
}

int init_data(t_table *table)
{
    int i;

    i = -1;
    table->all_threads_created = 0;
    table->stop = 0;
    table->n_of_running_threads = 0;
    table->philo = malloc(sizeof(t_philo) * table->n_of_philo);
    if (!table->philo)
        return (return_error_int("malloc failed"));
    table->forks = malloc(sizeof(pthread_mutex_t) * table->n_of_philo);
    if (!table->forks)
    {
        free(table->philo);
        return (return_error_int("malloc failed"));
    }
    if (init_mutexes(table) != 0 || philo_init(table) != 0)
    {
        free(table->philo);
        free(table->forks);
        return (1);
    }
    return (0);
}
