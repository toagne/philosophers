/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:26:27 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/05 11:22:47 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers(t_table *table)
{
	int			i;

	i = -1;
	if (table->n_of_times_to_eat == 0 || table->n_of_philo == 0)
	{
		free_table(table);
		return (0);
	}
	else
		while (++i < table->n_of_philo)
			if (pthread_create(&table->philo[i].thread, NULL,
					&routine, &table->philo[i]) != 0)
				return (clean_all(table, ROUTINE_THREAD, i - 1));
	if (pthread_create(&table->monitor_thread, NULL,
			&monitor_routine, table) != 0)
		return (clean_all(table, MONITOR_THREAD, table->n_of_philo));
	table->start = get_time(MILLISEC);
	safe_set_long(&table->table_lock, &table->all_threads_created, 1);
	return (clean_all(table, FINISHED, table->n_of_philo));
}

int	main(int argc, char **argv)
{
	t_table		*table;

	table = NULL;
	if (argc < 5 || argc > 6)
	{
		write(2, "wrong n of arguments\n", 21);
		return (EXIT_FAILURE);
	}
	table = malloc(sizeof(t_table));
	if (create_table(argv, table) != 0)
		return (EXIT_FAILURE);
	if (init_data(table) != 0)
		return (EXIT_FAILURE);
	if (philosophers(table) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
