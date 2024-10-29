/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:05:43 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/29 13:07:55 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n] != '\0')
		n++;
	return (n);
}

long	get_time()
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		write (2, "gettimeofday failed\n", 20);
		return (0);
	}
	return (tv.tv_sec *1000 + tv.tv_usec / 1000);
}

int	check_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->lock_action);
	if (philo->table->stop)
	{
		pthread_mutex_unlock(&philo->table->lock_action);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->lock_action);
	return (0);
}

int	return_error_int(char *str)
{
	printf(str);
	return (1);
}

char	*return_error_str(char *str)
{
	printf(str);
	return (NULL);
}