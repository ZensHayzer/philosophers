/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 06:01:14 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/13 06:01:56 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*eating_init(t_philo *philo)
{
	int	*eat_tab;

	eat_tab = malloc(sizeof(int) * 2);
	if (!eat_tab)
		return (NULL);
	if (philo->id == philo->data->nb_philo)
	{
		eat_tab[0] = philo->id - 1;
		eat_tab[1] = 0;
	}
	else
	{
		eat_tab[0] = philo->id;
		eat_tab[1] = philo->id - 1;
	}
	return (eat_tab);
}

int	eating_unlock(t_philo *philo, int uneeded, int *eat_tab)
{
	if (uneeded == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[eat_tab[0]]);
		return (free(eat_tab), 1);
	}
	else if (uneeded == 2)
	{
		pthread_mutex_unlock(&philo->data->forks[eat_tab[1]]);
		pthread_mutex_unlock(&philo->data->forks[eat_tab[0]]);
		return (free(eat_tab), 1);
	}
	else if (uneeded == 3)
	{
		pthread_mutex_unlock(&philo->data->forks[eat_tab[1]]);
		pthread_mutex_unlock(&philo->data->forks[eat_tab[0]]);
		return (free(eat_tab), 0);
	}
	return (0);
}
