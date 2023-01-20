/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:54:44 by ajeanne           #+#    #+#             */
/*   Updated: 2023/01/14 15:20:51 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	is_nb(char *entry)
{
	int	i;

	i = 0;
	while (entry[i])
	{
		if (i > 9)
			return (EXIT_FAILURE);
		if (entry[i] < '0' || entry[i] > '9')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_entry(char **input)
{
	int	i;

	i = 1;
	while (input[i])
	{
		if (is_nb)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}