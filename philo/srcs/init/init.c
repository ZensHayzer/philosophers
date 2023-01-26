/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:14:05 by ajeanne           #+#    #+#             */
/*   Updated: 2023/01/26 08:10:15 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks_tab(t_data data)
{
	int	i;

	i = 0;
	data.forks = malloc(sizeof(pthread_mutex_t) * data.nb_philo); //TODO TO FREE
	if (!data.forks)
		return (EXIT_FAILURE);
	while (i < data.nb_philo)
	{
		if(pthread_mutex_init(&data.forks[i], NULL))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_data(char **input, t_data data)
{
	data.nb_philo = ft_atoi(input[1]);
	data.t_eat = ft_atoi(input[2]);
	data.t_sleep = ft_atoi(input[3]);
	if (input[4])
		data.t_must_eat = ft_atoi(input[4]);
	else
		 data.t_must_eat = 0;
	if (pthread_mutex_init(&data.dead_phil, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data.write, NULL))
		return (EXIT_FAILURE);
	if (init_forks_tab(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}