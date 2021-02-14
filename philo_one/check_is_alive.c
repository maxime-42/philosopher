/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_alive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 17:26:21 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/13 20:00:29 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <semaphore.h>

/*
*	check if the philosophizing eats late
*	if the philosophizing eats late -> exit programe return DIE
*/
static int				check_time_meals(t_philosopher philosopher)
{
	long				time_actuel;
	long				time_difference;

	time_actuel = get_actuel_time();
	time_difference = time_actuel - philosopher.time_last_meal;
	if ((time_actuel - philosopher.time_last_meal) >= g_info.time_to_die)
	{
		printf("philosopher id %d | time %ld | difference_time = %ld time_to_die =  %d\n",philosopher.id, time_actuel, time_difference, g_info.time_to_die);
		return (DIE);
	}
	return (0);
}

/*
	check if a philosopher is dead
*/

void					check_is_alive(t_philosopher philosopher[])
{
	int					id;
	int					ret;

	while (1)
	{
		id = -1;
		while (++id < g_info.nb_philo)
		{
			ret = check_time_meals(philosopher[id]);
			if (ret == DIE)
			{
				printf("philosopher die\n");
				exit (0);
			}
		}
		usleep(1000);
	}
}