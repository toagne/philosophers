/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:05:43 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/05 10:12:10 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_time_option time_option)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (return_error_int("gettimeofday failed\n"));
	else if (time_option == MILLISEC)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	else if (time_option == MICROSEC)
		return (tv.tv_sec * 1000000 + tv.tv_usec);
	return (-1);
}

void	ft_usleep(long input_time, t_table *table)
{
	long	current_time;

	current_time = get_time(MICROSEC);
	while (get_time(MICROSEC) - current_time < input_time)
	{
		if (check_stop(table))
			break ;
		usleep(500);
	}
}

void	safe_printf(t_philo *philo, char *str)
{
	long	time;

	pthread_mutex_lock(&philo->table->printf_lock);
	time = get_time(MILLISEC) - philo->table->start;
	if (!check_stop(philo->table))
		printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->printf_lock);
}

void	destroy_mutex_array(pthread_mutex_t *mutex, t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_of_philo)
		pthread_mutex_destroy(&mutex[i]);
}
