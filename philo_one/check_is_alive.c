/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_alive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 17:26:21 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/16 19:15:34 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <semaphore.h>

/*
**	tihis check two things:
**		1-if all philosophizing them all have eaten enough
**		2-if a philosopher has to eat late so he dies.
*/

static int				state_of_philosopher(t_philosopher philosopher)
{
	long				time_actuel;
	long				time_difference;

	time_actuel = get_actuel_time();
	time_difference = time_actuel - philosopher.time_last_meal;
	if (g_info.current_number_of_meals == g_info.limit_nb_meal)
	{
		printf("Every one has eaten enought\n");
		return (EVERY_ONE_HAS_EAT_ENOUGHT);
	}
	else if ((time_actuel - philosopher.time_last_meal) >= g_info.time_to_die)
	{
		printf("philosopher id %d | time %ld | difference_time = %ld time_to_die =  %d\n",philosopher.id, time_actuel, time_difference, g_info.time_to_die);
		return (DIE);
	}
	return (0);
}


/*
** this function travel each philosophe one by one
** checks the state of each of them
*/

int						check_is_alive(t_philosopher philosopher[])
{
	int					id;
	int					ret;

	while (1)
	{
		id = -1;
		while (++id < g_info.nb_philo)
		{
			ret = state_of_philosopher(philosopher[id]);
			if (ret == DIE || ret == EVERY_ONE_HAS_EAT_ENOUGHT)
			{
				return (ret);
			}
		}
		usleep(1000);
	}
	return (ret);
}
