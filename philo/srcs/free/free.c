/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 00:22:12 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/13 03:22:45 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_exit(t_data *data)
{
	if (data->ate)
		free(data->ate);
	if (data->forks)
		free(data->forks);
	if (data->philo_tab)
		free(data->philo_tab);
	if (data->nb_ate)
		free(data->nb_ate);
}
