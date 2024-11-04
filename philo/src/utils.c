/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:05:43 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/04 16:45:31 by mpellegr         ###   ########.fr       */
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
	//long	elapsed;
	//long	rem;
    //struct timeval  start;
    //struct timeval  end;
	//long	real_time;

	current_time = get_time(MICROSEC);
	while (get_time(MICROSEC) - current_time < input_time)
	{
		
		if (check_stop(table))
			break ;
		//gettimeofday(&start, NULL);
		usleep(500);
		//gettimeofday(&end, NULL);
		//real_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
		//if (real_time > 500)
		//	usleep(500 - (real_time - 500));
		/*elapsed = get_time(MICROSEC) - current_time;
		rem = input_time - elapsed;
		if (rem > 10000)
			usleep(5000);
		else if (rem > 1000)
			usleep(500);
		else
			while (get_time(MICROSEC) - current_time < input_time)
				;*/
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
