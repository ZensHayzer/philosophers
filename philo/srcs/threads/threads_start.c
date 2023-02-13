/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 04:48:56 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/13 13:23:53 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	threads_start(t_data data)
{
	int			i;
	pthread_t	p_thread_monitor;

	i = 0;
	while (i < data.nb_philo)
	{
		data.philo_tab[i].data = &data;
		data.philo_tab[i].id = i + 1;
		data.philo_tab[i].nb_ate = 0;
		data.philo_tab[i].p_thread = 0;
		data.philo_tab[i].last_eat = 0;
		pthread_create(&(data.philo_tab[i].p_thread), NULL, &routine,
			(void *)&data.philo_tab[i]);
		i++;
	}
	pthread_create(&p_thread_monitor, NULL, &dead_checker, (void *)&data);
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_join(data.philo_tab[i].p_thread, NULL);
		i++;
	}
	pthread_join(p_thread_monitor, NULL);
}
