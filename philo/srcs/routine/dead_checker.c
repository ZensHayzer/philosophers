/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:05:01 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/13 13:26:49 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_phil);
	if (data->is_dead)
		return (pthread_mutex_unlock(&data->dead_phil), EXIT_FAILURE);
	pthread_mutex_unlock(&data->dead_phil);
	return (EXIT_SUCCESS);
}

int	all_ate(t_data *data)
{
	int	i;
	int	ate;

	i = 0;
	ate = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->nb_ate[i]);
		if (data->philo_tab[i].nb_ate >= data->t_must_eat)
			ate++;
		pthread_mutex_unlock(&data->nb_ate[i]);
		i++;
	}
	if (ate == data->nb_philo)
	{
		pthread_mutex_lock(&data->dead_phil);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->dead_phil);
		return (1);
	}
	return (0);
}

void	dead_printer(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->ate[i]);
		if (((gettime() - data->start) - data->philo_tab[i].last_eat)
			> data->t_die && !(data->is_dead))
		{
			pthread_mutex_lock(&data->dead_phil);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->dead_phil);
			pthread_mutex_lock(&data->write);
			printf("%ld %d died\n",
				(gettime() - data->start), data->philo_tab[i].id);
			pthread_mutex_unlock(&data->write);
		}
		pthread_mutex_unlock(&data->ate[i]);
		i++;
	}
}

void	*dead_checker(void *arg)
{
	t_data	*data;

	data = arg;
	while (!philo_dead(data) && ((data->t_must_eat) == -1 || !all_ate(data)))
	{
		dead_printer(data);
		usleep(500);
	}
	return (NULL);
}
