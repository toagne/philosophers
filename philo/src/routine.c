/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:49:25 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/30 16:52:15 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	safe_printf(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	safe_printf(philo, "has taken a fork");
}

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = get_time(MILLISEC);
	philo->n_of_meals++;
	pthread_mutex_unlock(&philo->philo_lock);
	safe_printf(philo, "is eating");
	ft_usleep(philo->table->time_to_eat * 1000, philo);
	if (philo->table->n_of_times_to_eat > 0 && philo->n_of_meals == philo->table->n_of_times_to_eat)
	{
		pthread_mutex_lock(&philo->philo_lock);
		philo->is_full = true;
		pthread_mutex_unlock(&philo->philo_lock);
	}
}

static void	ft_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

static void	ft_sleep(t_philo *philo)
{
	safe_printf(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep * 1000, philo);
}

/*bool	get_bool(pthread_mutex_t *mutex, bool *var)
{
	bool safe_var;

	pthread_mutex_lock(mutex);
	safe_var = *var;
	pthread_mutex_unlock(mutex);
	return (safe_var);
}*/

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	
	wait_all_threads_to_be_created(philo);

	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = get_time(MILLISEC);
	pthread_mutex_unlock(&philo->philo_lock);

	pthread_mutex_lock(&philo->table->table_lock);
	philo->table->n_of_running_threads++;
	pthread_mutex_unlock(&philo->table->table_lock);

	while (!check_stop(philo->table))
	{
		if (philo->is_full)
			break ;
		ft_take_forks(philo);
		ft_eat(philo);
		ft_release_forks(philo);
		ft_sleep(philo);
		safe_printf(philo, "is thinking");//ft_think(philo);
	}
	return (NULL);
}