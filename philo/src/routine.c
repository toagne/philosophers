/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:49:25 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/29 13:07:52 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
static void	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("%d has taken a fork\n", philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("%d has taken a fork\n", philo->id);
}

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->lock_action);
	philo->n_of_meals++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->lock_action);
	printf("%d is eating\n", philo->id);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	ft_sleep(t_philo *philo)
{
	printf("%d is sleeping", philo->id);
	usleep(philo->table->time_to_sleep * 1000);
}
*/
void	*routine(void *ptr)
{
	t_philo	*philo;
	int		stop;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->table->lock_action);
	while (!philo->table->all_threads_created)
		;
	pthread_mutex_unlock(&philo->table->lock_action);
	while (!check_stop(philo))
	{
		
		//	ft_take_fork(philo);
		//	ft_eat(philo);
		//	ft_sleep(philo);
		//	printf("%d is thinking", philo->id);
	}
	return (NULL);
}