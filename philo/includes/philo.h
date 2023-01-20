/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:01:48 by ajeanne           #+#    #+#             */
/*   Updated: 2023/01/14 15:31:18 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

/**************
 * STRUCTURES *
 **************/

typedef struct s_data
{
    int	nb_philo;
    int	t_eat;
    int	t_sleep;
    int	t_die;
    int	t_must_eat;
}	t_data;

/*************
 * FUNCTIONS *
 * ***********/

// init/init
void	init_data(char **input, t_data data);

// utils/utils
int	ft_atoi(char *str);

// check/check_entry
int	check_entry(char **input);
#endif