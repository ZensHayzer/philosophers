/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:59:43 by ajeanne           #+#    #+#             */
/*   Updated: 2023/01/14 15:08:56 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
    t_data  data;
    
	if (argc > 4 && !check_entry(argv))
    {
        init_data(argv, data);
    }
    return (EXIT_FAILURE);
}