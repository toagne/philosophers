/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:40:08 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/03 18:18:30 by giuls            ###   ########.fr       */
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
        {
            while (--i >= 0)
                pthread_mutex_destroy(&table->philo[i].philo_lock);
            destroy_mutex_array(table->forks, table);
            pthread_mutex_destroy(&table->table_lock);
            pthread_mutex_destroy(&table->printf_lock);
            return (return_error_int("pthread_mutex_init failed"));
        }   
    }
    return (0);
}

static int  init_mutexes(t_table *table)
{
    int i;

    if (pthread_mutex_init(&table->table_lock, NULL))
        return (return_error_int("pthread_mutex_init failed"));
    if (pthread_mutex_init(&table->printf_lock, NULL))
    {
        pthread_mutex_destroy(&table->table_lock);
        return (return_error_int("pthread_mutex_init failed"));
    }
    i = -1;
    while (++i < table->n_of_philo)
    {
        if (pthread_mutex_init(&table->forks[i], NULL))
        {
            while (--i >= 0)
                pthread_mutex_destroy(&table->forks[i]);
            pthread_mutex_destroy(&table->table_lock);
            pthread_mutex_destroy(&table->printf_lock);
            return (return_error_int("pthread_mutex_init failed"));
        }
    }
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
    {
        free_table(table);
        return (return_error_int("malloc failed"));
    }
    table->forks = malloc(sizeof(pthread_mutex_t) * table->n_of_philo);
    if (!table->forks)
    {
        free_table(table);
        return (return_error_int("malloc failed"));
    }
    if (init_mutexes(table) != 0 || philo_init(table) != 0)
    {
        free_table(table);
        return (1);
    }
    return (0);
}
