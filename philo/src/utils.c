/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:05:43 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/30 14:36:59 by mpellegr         ###   ########.fr       */
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
		return (tv.tv_sec *1000 + tv.tv_usec / 1000);
	else if (time_option == MICROSEC)
		return (tv.tv_sec *1000000 + tv.tv_usec);
	return (-1);
}

int	check_stop(t_table *table)
{
	pthread_mutex_lock(&table->table_lock);
	if (table->stop)
	{
		pthread_mutex_unlock(&table->table_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->table_lock);
	return (0);
}

void    ft_usleep(long input_time, t_philo *philo)
{
    long current_time;
    long elapsed;
    long rem;

    current_time = get_time(MICROSEC);
    //printf("initial time = %ld\n", current_time);
    while (get_time(MICROSEC) - current_time < input_time)
    {
		if (check_stop(philo->table))
			break ;
        elapsed = get_time(MICROSEC) - current_time;
        //printf("elapsed = %lu\n", elapsed);
        rem = input_time - elapsed;
        //printf("rem = %lu\n", rem);
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
	//check if philo full or check stop
	pthread_mutex_lock(&philo->table->printf_lock);
	printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->printf_lock);
}