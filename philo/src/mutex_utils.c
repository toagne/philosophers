/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:59:19 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/04 09:48:58 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_set_long(pthread_mutex_t *mutex, long *var, long value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

long	safe_get_long(pthread_mutex_t *mutex, long var)
{
	long	safe_var;

	pthread_mutex_lock(mutex);
	safe_var = var;
	pthread_mutex_unlock(mutex);
	return (safe_var);
}

void	safe_increase_long(pthread_mutex_t *mutex, long *var)
{
	pthread_mutex_lock(mutex);
	(*var)++;
	pthread_mutex_unlock(mutex);
}
