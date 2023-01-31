/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:54:44 by ajeanne           #+#    #+#             */
/*   Updated: 2023/01/31 17:59:18 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	isok_nb(char *nb)
{
	int	i;

	i = 0;
	while ((nb[i] >= 9 && nb[i] <= 13) || nb[i] == 32)
		i++;
	if (nb[i] == '+' || nb[i] == '-')
		i++;
	if (nb[i] < '0' || nb[i] > '9')
		return (EXIT_FAILURE);
	while (nb[i] >= '0' && nb[i] <= '9')
		i++;
	if (nb[i])
		return (EXIT_FAILURE);
	if (ft_atoi(nb) > INT_MAX || ft_atoi(nb) < INT_MIN)
		return (EXIT_FAILURE);
	if (ft_atoi(nb) < 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_under_200(char *nb)
{
	if (atoi(nb) > 200)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_entry(char **input)
{
	int	i;

	i = 1;
	while (input[i])
	{
		if (!input[i])
			return (EXIT_FAILURE);
		if (isok_nb(input[i]))
			return (EXIT_FAILURE);
		if (is_under_200(input[i]) && i == 1)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
