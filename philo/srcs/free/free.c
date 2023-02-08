/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 00:22:12 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/08 18:57:40 by ajeanne          ###   ########.fr       */
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
}
