/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:26:27 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/29 13:07:50 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers(t_table *table)
{
	int			i;

	i = -1;
	if  (table->n_of_times_to_eat == 0)
		return ;
	else if (table->n_of_philo == 1)
		; //single philo
	else
	{
		while (++i < table->n_of_philo)
		{
			if(pthread_create(&table->philo[i].thread, NULL, &routine, &table->philo[i]) != 0)
			{
				//clean
				printf("create threads failed\n");
				return (0);
			}
		}
	}
	table->start = get_time();

	pthread_mutex_lock(&table->lock_action);
	table->all_threads_created = true;
	pthread_mutex_unlock(&table->lock_action);
	
	i = -1;
	while (++i < table->n_of_philo)
		pthread_join(table->philo[i].thread, NULL);
}

int main(int argc, char **argv)
{
	t_table		table;

	if (argc < 5 || argc > 6)
	{
		write(2, "wrong n of arguments\n", 21);
		return (EXIT_FAILURE);
	}
	if (create_table(argv, &table) != 0)
		return (EXIT_FAILURE);
	if (init_data(&table) != 0)
		return (EXIT_FAILURE);
	if (!philosophers(&table))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
