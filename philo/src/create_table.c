/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:32:08 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/11 10:55:15 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(char *num)
{
	int n;
	int i;

	i = -1;
	n = 0;
	while (num[++i])
		n = n * 10 + (num[i] - '0');
	return (n);
}

static int	ft_isdigit(int arg)
{
	if (arg >= 48 && arg <= 57)
		return (1);
	return (0);
}

static void	validate_input(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				write (2, "non numeric argument\n", 21);
				exit (EXIT_FAILURE);
			}
		}
	}
}

void	create_table(char **argv, t_table *table)
{
	int	i;

	validate_input(argv);
	table->n_of_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->n_of_times_to_eat = ft_atoi(argv[5]);
	table->start = 0;
	table->philo = malloc(sizeof(t_philo) * table->n_of_philo);
	table->forks = malloc(sizeof(pthread_mutex_t)  * table->n_of_philo);
	if (pthread_mutex_init(&table->lock_action, NULL) != 0)
	{
		printf("mutex_init failed for forks");
		exit (EXIT_FAILURE);
	}
	i = -1;
	while (++i < table->n_of_philo)
		pthread_mutex_init(&table->forks[i], NULL);
	i = -1;
	while (++i < table->n_of_philo)
	{
		table->philo[i].n_of_meals = 0;
		table->philo[i].last_meal = 0;
		table->philo[i].id = i + 1;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->n_of_philo];
	}
}