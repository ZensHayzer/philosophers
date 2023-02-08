/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:05:01 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/08 19:07:31 by ajeanne          ###   ########.fr       */
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
		pthread_mutex_lock(&data->ate[i]);
		if (data->philo_tab[i].nb_eated == data->t_must_eat)
			ate++;
		pthread_mutex_unlock(&data->ate[i]);
		i++;
	}
	if (ate == data->nb_philo)
	{
		data->is_dead = 1;
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
		if (((gettime() - data->start) - data->philo_tab[i].last_eat)
		> data->t_die && !(data->is_dead))
		{
			pthread_mutex_lock(&data->write);
			printf("%ld PHILOSOPHER %d IS DEAD\n",
			(gettime() - data->start), data->philo_tab[i].id);
			pthread_mutex_unlock(&data->write);
			data->is_dead = 1;
		}
		i++;
	}
}

void	*dead_checker(void *arg)
{
	t_data	*data;

	data = arg;
	while (!philo_dead(data) && (!(data->t_must_eat) || !all_ate(data)))
	{
		dead_printer(data);
	}
	return (NULL);
}
