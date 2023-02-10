/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:09:25 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/11 00:47:22 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock(t_philo *philo)
{
	if (philo->id == philo->data->nb_philo)
	{
		pthread_mutex_unlock(&philo->data->forks[0]);
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->forks[philo->id]);
	}
}

int	state(t_philo *philo, int s)
{
	pthread_mutex_lock(&philo->data->write);
	pthread_mutex_lock(&philo->data->dead_phil);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->write);
		return (pthread_mutex_unlock(&philo->data->dead_phil), 1);
	}
	pthread_mutex_unlock(&philo->data->dead_phil);
	if (s == 1)
		printf("%ld PHILOSOPHER %d TAKE A FORK\n",
			(gettime() - philo->data->start), philo->id);
	else if (s == 2)
		printf("%ld PHILOSOPHER %d IS SLEEPING\n",
			(gettime() - philo->data->start), philo->id);
	else if (s == 3)
		printf("%ld PHILOSOPHER %d IS THINKING\n",
			(gettime() - philo->data->start), philo->id);
	else if (s == 4)
		printf("%ld PHILOSOPHER %d IS EATING\n",
			(gettime() - philo->data->start), philo->id);
	else if (s == 5)
		printf("%ld PHILOSOPHER %d IS DEAD\n",
			(gettime() - philo->data->start), philo->id);
	pthread_mutex_unlock(&philo->data->write);
	return (0);
}

int	is_deadqm(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_phil);
	if (philo->data->is_dead)
		return (pthread_mutex_unlock(&philo->data->dead_phil), 1);
	pthread_mutex_unlock(&philo->data->dead_phil);
	return (0);
}

int	lock(t_philo *philo)
{
	if (philo->id == philo->data->nb_philo)
	{
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		if (state(philo, 1))
			return (pthread_mutex_unlock(&philo->data->forks[philo->id - 1]), 1);
		pthread_mutex_lock(&philo->data->forks[0]);
		if (state(philo, 1))
		{
			pthread_mutex_unlock(&philo->data->forks[0]);
			return (pthread_mutex_unlock(&philo->data->forks[philo->id - 1]), 1);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->id]);
		if (state(philo, 1))
			return (pthread_mutex_unlock(&philo->data->forks[philo->id]), 1);
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		if (state(philo, 1))
		{
			pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
			return (pthread_mutex_unlock(&philo->data->forks[philo->id]), 1);
		}
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while ((philo->data->t_must_eat == -1 || philo->nb_eated
			< philo->data->t_must_eat) && !is_deadqm(philo))
	{
		if (philo->id % 2 && !(philo->nb_eated))
			ft_sleep(philo->data->t_eat, philo);
		if (lock(philo))
			return (NULL);
		if (state(philo, 4))
			return (NULL);
		pthread_mutex_lock(&philo->data->ate[philo->id - 1]);
		philo->last_eat = gettime() - philo->data->start;
		philo->nb_eated++;
		if(ft_sleep(philo->data->t_eat, philo))
			return (unlock(philo), pthread_mutex_unlock(&philo->data->ate[philo->id - 1]), NULL);
		pthread_mutex_unlock(&philo->data->ate[philo->id - 1]);
		unlock(philo);
		if (state(philo, 2))
			return (NULL);
		if (ft_sleep(philo->data->t_sleep, philo))
			return (NULL);
		if (state(philo, 3))
			return (NULL);
	}
	return (NULL);
}
