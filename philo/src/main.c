/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:26:27 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/31 16:51:32 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_table *table)
{
	printf("%d %d %s\n", 0, table->philo[0].id, "has taken a fork");
	ft_usleep(table->time_to_die, table);
	printf("%d %d %s\n", table->time_to_die, table->philo[0].id, "died");
	return (0);
}

int	philosophers(t_table *table)
{
	int			i;

	i = -1;
	if  (table->n_of_times_to_eat == 0)
		return (0);
	else if (table->n_of_philo == 1)
		return (one_philo(table));
	else
	{
		while (++i < table->n_of_philo)
		{
			if (pthread_create(&table->philo[i].thread, NULL, &routine, &table->philo[i]) != 0)
			{
				//clean
				printf("create threads failed\n");
				return (1);
			}
		}
	}
	
	if (pthread_create(&table->monitor_thread, NULL, &monitor_routine, table) != 0)
	{
		//clean
		printf("create threads failed\n");
		return (1);
	}
	
	table->start = get_time(MILLISEC);
	
	safe_set_long(&table->table_lock, &table->all_threads_created, 1);
	
	i = -1;
	while (++i < table->n_of_philo)
		pthread_join(table->philo[i].thread, NULL);
	
	//safe_set_long(&table->table_lock, &table->stop, 1);

	pthread_join(table->monitor_thread, NULL);

	return (0);
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
	if (philosophers(&table) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
