/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:01:48 by ajeanne           #+#    #+#             */
/*   Updated: 2023/01/26 08:08:26 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>
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
	struct s_philo	*philo_tab;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_phil;
	pthread_mutex_t	write;
}		t_data;

typedef struct s_philo
{
	struct s_data	data;
	int				id;
	long			last_eat;
	pthread_t		p_thread;
}		t_philo;

/*************
 * FUNCTIONS *
 *************/

// init/init
int	init_data(char **input, t_data data);

// utils/utils
long	ft_atoi(const char *str);

// check/check_entry
int		check_entry(char **input);

// threads/threads_start
void	threads_start(t_philo philo, t_data data);
#endif