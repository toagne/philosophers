/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:26:27 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/08 09:57:24 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *num)
{
	int n;
	int i;

	i = -1;
	n = 0;
	while (num[++i])
		n = n * 10 + (num[i] - '0');
	return (n);
}

int	ft_isdigit(int arg)
{
	if (arg >= 48 && arg <= 57)
		return (1);
	return (0);
}

void	validate_input(char **argv)
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

void	create_table(char **argv, t_philo *philo)
{
	validate_input(argv);
	philo->n_of_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->n_of_times_to_eat = ft_atoi(argv[5]);
}

void	init_table(t_philo *philo)
{
	philo->n_of_philo = 0;
	philo->time_to_die = 0;
	philo->time_to_eat = 0;
	philo->time_to_sleep = 0;
	philo->n_of_times_to_eat = 0;
}

void	create_threads((t_philo philo))
{
	int			i;
	pthread_t	ptid[philo.n_of_philo]

	i = 0;
	while (i < philo.n_of_philo)
	{
		pthread_create(ptid[i], NULL, routine, NULL);
	}
}

int main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || argc > 6)
	{
		write(2, "wrong n of arguments\n", 21);
		exit (EXIT_FAILURE);
	}
	init_table(&philo);
	create_table(argv, &philo);
	create_threads(philo);
}
