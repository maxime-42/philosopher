/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:16:32 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/13 23:50:09 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h> 
#include <stdio.h> 

void					init_philosopher(t_philosopher philo[], int nb_philo)
{
	int					id;

	id = -1;
	while (++id < nb_philo)
	{
		philo[id].id = id;
		philo[id].time_last_meal = 0;
		philo[id].nb_meal = 0;
		philo[id].right = id;
		philo[id].left = (id + 1) % g_info.nb_philo;
	}
}

void					init_mutex(pthread_mutex_t fork[], pthread_mutex_t *end)
{
	int					id;

	id = -1;
	while (++id < g_info.nb_philo)
	{
		pthread_mutex_init(&fork[id], NULL);
	}
	pthread_mutex_init(end, NULL);
}

void					clear_semaphor(t_info *info)
{
	pthread_mutex_destroy(&g_info.fork);
	pthread_mutex_destroy(&g_info.end);
}