/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:49:25 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/31 15:53:12 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*static void	ft_take_forks(t_philo *philo)
{
	int	first_locked;
	int	second_locked;

	first_locked = 0;
	second_locked = 0;
	pthread_mutex_lock(philo->first_fork);
	first_locked = 1;
	safe_printf(philo, "has taken a fork");
	if (!check_stop(philo->table))
	{
		pthread_mutex_lock(philo->second_fork);
		second_locked = 1;
		safe_printf(philo, "has taken a fork");
	}
	if (!second_locked && first_locked)
		pthread_mutex_unlock(philo->first_fork);
}*/

/*static void	ft_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->first_fork);
		safe_printf(philo, "has taken a fork");
		pthread_mutex_lock(philo->second_fork);
		safe_printf(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->second_fork);
		safe_printf(philo, "has taken a fork");
		pthread_mutex_lock(philo->first_fork);
		safe_printf(philo, "has taken a fork");
	}
}*/

static int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	safe_printf(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	safe_printf(philo, "has taken a fork");
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = get_time(MILLISEC) - philo->table->start;
	philo->n_of_meals++;
	pthread_mutex_unlock(&philo->philo_lock);
	safe_printf(philo, "is eating");
	ft_usleep(philo->table->time_to_eat * 1000, philo->table);
	if (philo->table->n_of_times_to_eat > 0 && philo->n_of_meals == philo->table->n_of_times_to_eat)
		safe_set_long(&philo->philo_lock, &philo->is_full, 1);
	if (check_stop(philo->table))
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return (1);
	}
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return (0);
}
static void	ft_sleep(t_philo *philo)
{
	safe_printf(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep * 1000, philo->table);
}

void 	ft_think(t_philo *philo, int desync_threads)
{
	long	available_think_time;

	if (!desync_threads)
		safe_printf(philo, "is thinking");
	available_think_time = philo->table->time_to_eat * 2 - philo->table->time_to_sleep;
	if (available_think_time < 0)
		available_think_time = 0;
	if (desync_threads)
		ft_usleep(available_think_time * 0.5 * 1000, philo->table);
	else if (!desync_threads && philo->table->n_of_philo % 2 != 0)
		ft_usleep(available_think_time * 0.5 * 1000, philo->table);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	
	wait_all_threads_to_be_created(philo);
	
	//safe_set_long(&philo->philo_lock, &philo->last_meal, philo->table->start);
	
	safe_increase_long(&philo->table->table_lock, &philo->table->n_of_running_threads);
	
	if (philo->id % 2 != 0)
		ft_think(philo, 1);

	while (!check_stop(philo->table))
	{
		pthread_mutex_lock(&philo->philo_lock);
		if (philo->is_full)
		{
			pthread_mutex_unlock(&philo->philo_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->philo_lock);
		//ft_take_forks(philo);
		if (ft_eat(philo) != 0)
			break ;
		ft_sleep(philo);
		ft_think(philo, 0);
		//safe_printf(philo, "is thinking");//ft_think(philo);
	}
	return (NULL);
}
