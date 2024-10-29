/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:40:08 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/29 13:07:51 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void init_forks(t_table *table, int i)
{
    if (table->philo[i].id % 2 == 0)
    {
        table->philo[i].right_fork = &table->forks[i];
        table->philo[i].left_fork = &table->forks[(i + 1) % table->n_of_philo];
    }
    else
    {
        table->philo[i].right_fork = &table->forks[(i + 1) % table->n_of_philo];
        table->philo[i].left_fork = &table->forks[i];
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
        init_forks(table, i);
    }
}

int init_data(t_table *table)
{
    int i;

    i = -1;
    table->philo = malloc(sizeof(t_philo) * table->n_of_philo);
    if (!table->philo)
        return (return_error("malloc failed\n"));
    table->forks = malloc(sizeof(pthread_mutex_t) * table->n_of_philo);
    if (!table->forks)
    {
        free(table->philo);
        return (return_error("malloc failed\n"));
    }
    while (++i < table->n_of_philo)
    {
        if (pthread_mutex_init(&table->forks[i], NULL)) //destroy + clean
            return (return_error("mutex init failed\n"));
    }
    if (pthread_mutex_init(&table->lock_action, NULL)) //destroy + clean
        return (return_error("mutex init failed\n"));
    table->all_threads_created = false;
    table->stop = false;
    philo_init(table);
}