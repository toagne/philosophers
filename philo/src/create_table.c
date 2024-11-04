/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:32:08 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/04 10:01:08 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int arg)
{
	if (arg >= 48 && arg <= 57)
		return (1);
	return (0);
}

static int	ft_isspace(int arg)
{
	if ((arg >= 9 && arg <= 13) || arg == 32)
		return (1);
	return (0);
}

static char	*validate_input(char *str)
{
	int		len;
	char	*num;

	len = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (return_error_str("input is negative"));
	if (!ft_isdigit(*str))
		return (return_error_str("input is not a digit"));
	num = str;
	while (ft_isdigit(*str++))
		len++;
	if (len > 10)
		return (return_error_str("input bigger than INT_MAX"));
	return (num);
}

static long	ft_atol(char *str, int *err)
{
	long	num;

	num = 0;
	str = validate_input(str);
	if (!str)
		*err = 1;
	else
	{
		while (ft_isdigit(*str))
			num = num * 10 + (*str++ - '0');
		if (num > INT_MAX)
		{
			write (2, "input bigger than INT_MAX\n", 26);
			*err = 1;
		}
	}
	return (num);
}

int	create_table(char **argv, t_table *table)
{
	int	err;

	err = 0;
	table->n_of_philo = ft_atol(argv[1], &err);
	table->time_to_die = ft_atol(argv[2], &err);
	table->time_to_eat = ft_atol(argv[3], &err);
	table->time_to_sleep = ft_atol(argv[4], &err);
	if (argv[5])
		table->n_of_times_to_eat = ft_atol(argv[5], &err);
	else
		table->n_of_times_to_eat = -1;
	if (err == 1)
		return (1);
	return (0);
}
