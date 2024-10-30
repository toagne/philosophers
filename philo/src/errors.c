/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:26:56 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/30 10:40:27 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	return_error_int(char *str)
{
	printf("%s\n", str);
	return (1);
}

char	*return_error_str(char *str)
{
	printf("%s\n", str);
	return (NULL);
}