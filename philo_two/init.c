/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:16:32 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/19 21:51:16 by mkayumba         ###   ########.fr       */
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
		memset(&philo[id], 0, sizeof(t_philosopher));
		philo[id].id = id + 1;
	}
}

void					init_semaphor(t_info *info)
{
	sem_unlink("fork");
	sem_unlink("write");
	sem_unlink("end");
	info->fork = sem_open("fork", O_CREAT | O_RDWR, 0660, info->nb_philo / 2);
	info->write = sem_open("write", O_CREAT | O_RDWR, 0660, 1);
	info->end = sem_open("end", O_CREAT | O_RDWR, 0660, 1);
}

void					clear_semaphor(t_info *info)
{
	sem_close(info->fork );
	sem_close(info->write);
	sem_close(info->end);
}
