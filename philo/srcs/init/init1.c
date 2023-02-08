/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:46:03 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/08 18:57:13 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_ate_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->ate = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->ate)
		return (EXIT_FAILURE);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->ate[i] , NULL))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
