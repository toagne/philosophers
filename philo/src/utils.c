/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:05:43 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/04 11:00:53 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_time_option time_option)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (return_error_int("gettimeofday failed\n"));
	if (time_option == SEC)
		return (tv.tv_sec + tv.tv_usec / 1000000);
	else if (time_option == MILLISEC)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	else if (time_option == MICROSEC)
		return (tv.tv_sec * 1000000 + tv.tv_usec);
	return (-1);
}

void	ft_usleep(long input_time, t_table *table)
{
	long	current_time;
	long	elapsed;
	long	rem;

	current_time = get_time(MICROSEC);
	while (get_time(MICROSEC) - current_time < input_time)
	{
		if (check_stop(table))
			break ;
		elapsed = get_time(MICROSEC) - current_time;
		rem = input_time - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
		else
			while (get_time(MICROSEC) - current_time < input_time)
				;
	}
}

void	safe_printf(t_philo *philo, char *str)
{
	long	time;

	time = get_time(MILLISEC) - philo->table->start;
	pthread_mutex_lock(&philo->table->printf_lock);
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
