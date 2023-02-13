/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:14:05 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/13 06:10:36 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks_tab(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->nb_philo);
	if (!data->forks)
		return (EXIT_FAILURE);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_data(char **input, t_data *data)
{
	data->nb_philo = ft_atoi(input[1]);
	data->t_die = ft_atoi(input[2]);
	data->t_eat = ft_atoi(input[3]);
	data->t_sleep = ft_atoi(input[4]);
	data->is_dead = 0;
	data->start = gettime();
	if (input[5])
		data->t_must_eat = ft_atoi(input[5]);
	else
		data->t_must_eat = -1;
	if (pthread_mutex_init(&data->dead_phil, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->write, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_philo(t_philo philo, t_data *data)
{
	philo.data = data;
	philo.id = 0;
	philo.nb_ate = 0;
	philo.p_thread = 0;
	philo.last_eat = 0;
	return (EXIT_SUCCESS);
}

int	init_philo_tab(t_data *data)
{
	int	i;

	i = 0;
	data->philo_tab = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo_tab)
		return (EXIT_FAILURE);
	while (i < data->nb_philo)
	{
		if (init_philo(data->philo_tab[i], data))
			return (1);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	initialization(char **input, t_data *data)
{
	if (init_data(input, data))
		return (EXIT_FAILURE);
	if (init_forks_tab(data))
		return (EXIT_FAILURE);
	if (init_philo_tab(data))
		return (EXIT_FAILURE);
	if (init_ate_mutex(data))
		return (EXIT_FAILURE);
	if (init_nb_ate_mutex(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
