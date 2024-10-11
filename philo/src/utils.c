/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:38:37 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/10 17:41:20 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_time()
{
	long long int	time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec *1000 + tv.tv_usec / 1000;
	return (time);
}