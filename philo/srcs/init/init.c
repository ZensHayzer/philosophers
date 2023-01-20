/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:14:05 by ajeanne           #+#    #+#             */
/*   Updated: 2023/01/14 14:48:52 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	init_data(char **input, t_data data)
{
	data.nb_philo = ft_atoi(input[1]);
	data.t_eat = ft_atoi(input[2]);
	data.t_sleep = ft_atoi(input[3]);
	if (input[4])
		data.t_must_eat = ft_atoi(input[4]);
	else
		 data.t_must_eat = 0;
}