/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:59:43 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/08 07:05:30 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc > 4 && argc < 7 && !check_entry(argv))
	{
		if (initialization(argv, &data))
			return (free_exit(&data), EXIT_FAILURE);
		threads_start(data);
		return (free_exit(&data), EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
