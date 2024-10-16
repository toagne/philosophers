/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:26:27 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/10 17:41:22 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	create_threads(t_table *table)
{
	int			i;

	i = 0;
	while (i < table->n_of_philo)
	{
		table->start = get_time();
		pthread_create(&table->philo[i].thread, NULL, &routine, &table->philo[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_table		table;

	if (argc < 5 || argc > 6)
	{
		write(2, "wrong n of arguments\n", 21);
		exit (EXIT_FAILURE);
	}
	create_table(argv, &table);
	create_threads(&table);
}
