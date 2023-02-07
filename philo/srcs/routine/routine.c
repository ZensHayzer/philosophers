/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:09:25 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/06 19:49:06 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock(t_philo *philo)
{
	if (philo->id != philo->data->nb_philo)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->forks[philo->id]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->forks[0]);
	}
}

void	state(t_philo *philo, int s)
{
	pthread_mutex_lock(&philo->data->write);
	if (s == 1)
		printf("%ld PHILOSOPHER %d TAKE A FORK\n", (gettime() - philo->data->start), philo->id);
	else if (s == 2)
		printf("%ld PHILOSOPHER %d IS SLEEPING\n", (gettime() - philo->data->start), philo->id);
	else if (s == 3)
		printf("%ld PHILOSOPHER %d IS THINKING\n", (gettime() - philo->data->start), philo->id);
	else if (s == 4)
		printf("%ld PHILOSOPHER %d IS EATING\n", (gettime() - philo->data->start), philo->id);
	pthread_mutex_unlock(&philo->data->write);
}

int	is_deadqm(t_philo *philo)
{
	if (philo->data->is_dead)
		return (1);
	else if ((gettime() - philo->last_eat) > philo->data->t_die)
	{
		state_dead(philo);
		pthread_mutex_lock(&philo->data->dead_phil);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->dead_phil);
		return (1);
	}
	return (0);
}

int	lock(t_philo *philo)
{
	if (philo->id != philo->data->nb_philo)
	{
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		if (philo->last_eat && is_deadqm(philo))
			return (unlock(philo), 1);
		state(philo, 1);
		pthread_mutex_lock(&philo->data->forks[philo->id]);
		if (philo->last_eat && is_deadqm(philo))
			return (unlock(philo), 1);
		state(philo, 1);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		if (philo->last_eat && is_deadqm(philo))
			return (unlock(philo), 1);
		state(philo, 1);
		pthread_mutex_lock(&philo->data->forks[0]);
		if (philo->last_eat && is_deadqm(philo))
			return (unlock(philo), 1);
		state(philo, 1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while ((philo->data->t_must_eat != 0 && philo->nb_eated != philo->data->t_must_eat) || !(philo->data->is_dead))
	{
		if (philo->id % 2 && !(philo->nb_eated))
			usleep(philo->data->t_eat * 1000);
		if (lock(philo))
			return (NULL);
		state(philo, 4);
		philo->last_eat = gettime() - philo->data->start;
		philo->nb_eated++;
		usleep(philo->data->t_eat * 1000);
		unlock(philo);
		if (philo->last_eat && is_deadqm(philo))
			return (unlock(philo), NULL);
		state(philo, 2);
		usleep(philo->data->t_sleep * 1000);
		if (philo->last_eat && is_deadqm(philo))
			return (unlock(philo), NULL);
		state(philo, 3);
	}
	return (NULL);
}
