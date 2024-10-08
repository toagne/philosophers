/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:32:44 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/08 09:41:18 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_philo
{
	int	n_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_of_times_to_eat;
}	t_philo;

#endif
