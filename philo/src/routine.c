/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:49:25 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/04 11:00:01 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	printf("%d %d %s\n", 0, philo[0].id, "has taken a fork");
	ft_usleep(philo->table->time_to_die, philo->table);
	pthread_mutex_unlock(philo->first_fork);
	return (NULL);
}

static int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	safe_printf(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	safe_printf(philo, "has taken a fork");
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = get_time(MILLISEC) - philo->table->start;
	pthread_mutex_unlock(&philo->philo_lock);
	safe_printf(philo, "is eating");
	ft_usleep(philo->table->time_to_eat * 1000, philo->table);
	pthread_mutex_lock(&philo->philo_lock);
	philo->n_of_meals++;
	pthread_mutex_unlock(&philo->philo_lock);
	if (philo->table->n_of_times_to_eat > 0
		&& philo->n_of_meals == philo->table->n_of_times_to_eat)
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

void	ft_think(t_philo *philo, int desync_threads)
{
	long	avail_think_time;
	int		t_to_eat;
	int		t_to_sleep;

	t_to_eat = philo->table->time_to_eat;
	t_to_sleep = philo->table->time_to_sleep;
	if (!desync_threads)
		safe_printf(philo, "is thinking");
	avail_think_time = t_to_eat * 2 - t_to_sleep;
	if (avail_think_time < 0)
		avail_think_time = 0;
	if (desync_threads)
		ft_usleep(avail_think_time * 0.5 * 1000, philo->table);
	else if (!desync_threads && philo->table->n_of_philo % 2 != 0)
		ft_usleep(avail_think_time * 0.5 * 1000, philo->table);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	wait_all_threads_to_be_created(philo);
	safe_increase_long(&philo->table->table_lock,
		&philo->table->n_of_running_threads);
	if (philo->table->n_of_philo == 1)
		return (one_philo(philo));
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
		if (ft_eat(philo) != 0)
			break ;
		ft_sleep(philo);
		ft_think(philo, 0);
	}
	return (NULL);
}
