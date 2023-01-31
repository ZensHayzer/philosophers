/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 04:48:56 by ajeanne           #+#    #+#             */
/*   Updated: 2023/01/31 19:37:59 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	threads_start(t_data data)
{
	int	i;

	i = 0;
	while (i < data.nb_philo)
	{
		data.philo_tab[i].data = &data;
		data.philo_tab[i].id = i + 1;
		pthread_create(&(data.philo_tab[i].p_thread), NULL, &routine, (void *)&data.philo_tab[i]);
		i++;
	}
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_join(data.philo_tab[i].p_thread, NULL);
		i++;
	}
}
