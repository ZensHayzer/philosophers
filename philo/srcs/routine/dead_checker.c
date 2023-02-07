/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:05:01 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/06 19:00:16 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_phil);
	if (data->is_dead)
		return (EXIT_FAILURE);
	pthread_mutex_unlock(&data->dead_phil);
	return (EXIT_SUCCESS);
}

void	state_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	printf("%ld PHILOSOPHER %d IS DEAD\n", (gettime() - philo->data->start), philo->id);
}

int	all_ate(t_data *data)
{
	int	i;
	int	ate;
	
	i= 0;
	ate = 0;
	while (i < data->nb_philo)
	{
		if(data->philo_tab[i].nb_eated < data->t_must_eat)
			ate++;
		i++;
	}
	if (ate == data->nb_philo)
		return (1);
	return (0);
}

void	*dead_checker(void *arg)
{
	t_data	*data;
	int		i;
	
	data = arg;
	i = 0;
	while (!philo_dead(data) && (!(data->t_must_eat) || !all_ate(data)))
	{
		i++;
		if (i == data->nb_philo)
			i = 0;
	}
	exit (1);
	return (NULL);	
}