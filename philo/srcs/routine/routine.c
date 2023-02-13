/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:09:25 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/13 13:28:06 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	solo_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	printf("%ld %d has taken a fork\n",
		(gettime() - philo->data->start), philo->id);
	pthread_mutex_unlock(&philo->data->write);
}

int	routine_write(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->data->write);
	if (is_deadqm(philo))
		return (pthread_mutex_unlock(&philo->data->write), 1);
	if (state == 1)
		printf("%ld %d has taken a fork\n",
			(gettime() - philo->data->start), philo->id);
	else if (state == 2)
		printf("%ld %d is eating\n",
			(gettime() - philo->data->start), philo->id);
	else if (state == 3)
		printf("%ld %d is sleeping\n",
			(gettime() - philo->data->start), philo->id);
	else if (state == 4)
		printf("%ld %d is thinking\n",
			(gettime() - philo->data->start), philo->id);
	pthread_mutex_unlock(&philo->data->write);
	return (0);
}

int	eating_step(t_philo *philo)
{
	int	*eat_tab;

	eat_tab = eating_init(philo);
	if (!eat_tab)
		return (1);
	pthread_mutex_lock(&philo->data->forks[eat_tab[0]]);
	if (routine_write(philo, 1))
		return (eating_unlock(philo, 1, eat_tab));
	pthread_mutex_lock(&philo->data->forks[eat_tab[1]]);
	if (routine_write(philo, 1))
		return (eating_unlock(philo, 2, eat_tab));
	if (routine_write(philo, 2))
		return (eating_unlock(philo, 2, eat_tab));
	pthread_mutex_lock(&philo->data->ate[philo->id - 1]);
	philo->last_eat = gettime() - philo->data->start;
	pthread_mutex_unlock(&philo->data->ate[philo->id - 1]);
	pthread_mutex_lock(&philo->data->nb_ate[philo->id - 1]);
	philo->nb_ate++;
	pthread_mutex_unlock(&philo->data->nb_ate[philo->id - 1]);
	if (ft_sleep(philo->data->t_eat, philo))
		return (eating_unlock(philo, 2, eat_tab));
	return (eating_unlock(philo, 3, eat_tab));
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
		return (solo_philo(philo), NULL);
	if (philo->id % 2)
		ft_sleep(philo->data->t_eat, philo);
	while (!is_deadqm(philo))
	{
		if (eating_step(philo))
			return (NULL);
		if (routine_write(philo, 3))
			return (NULL);
		if (ft_sleep(philo->data->t_sleep, philo))
			return (NULL);
		if (routine_write(philo, 4))
			return (NULL);
	}
	return (NULL);
}
