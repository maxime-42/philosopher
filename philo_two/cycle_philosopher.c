/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:20:20 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/21 16:09:44 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <semaphore.h>

/*
** step 1 : if a philosophe eaten enough :
**		"g_info.current_number_of_meals" is equal at "g_info.limit_nb_mea"
**
** step 2 : calcule if a philosophe eaten enough to print message
**
**if step 1 et step 2 is not true this function return 0
*/

static int			state_of_philosopher(t_philosopher philosopher)
{
	long			time_actuel;

	time_actuel = get_actuel_time();
	if (g_info.current_number_of_meals == g_info.limit_nb_meal)
	{
		return (EVERY_ONE_HAS_EAT_ENOUGHT);
	}
	else if ((time_actuel - philosopher.time_last_meal) >= g_info.time_to_die)
	{
		g_info.time_actuel = time_actuel;
		g_info.time_difference = time_actuel - philosopher.time_last_meal;
		g_info.philo_dead = philosopher.id;
		return (DIE);
	}
	return (0);
}

/*
** each 1000 millisecond go through all the philosopher for :
**		check if a philosophe eaten late to print message
**		check if a philosophe eaten enough to print message
*/

int					check_is_alive(t_philosopher philosopher[])
{
	int				id;
	int				ret;

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

static void			philosopher_eat(t_philosopher *philosopher)
{
	sem_wait(g_info.fork);
	printf("%ld %d has taken a fork\n", get_actuel_time(), philosopher->id);
	printf("%ld %d has taken a fork\n", get_actuel_time(), philosopher->id);
	philosopher->time_last_meal = get_actuel_time();
	printf("%ld %d is eating \n", philosopher->time_last_meal, philosopher->id);
	sem_wait(g_info.end);
	sem_post(g_info.end);
	usleep(g_info.time_to_eat * 1000);
	sem_post(g_info.fork);
}

/*
**	this function allow to try to take fork
**	if the fork is unable philosopher will wait
*/

static void			philosopher_sleep_and_thinking(t_philosopher *philosopher)
{
	printf("%ld %d is sleeping\n", get_actuel_time(), philosopher->id);
	usleep(g_info.time_to_sleep * 1000);
	printf("%ld %d is thinking\n", get_actuel_time(), philosopher->id);
}

/*
**step 1 :   "loop" correspond at number of meals
**           so "loop" equal to number of meals.
**
** if number some meals is not present it will be infinite loop
** so loop != INFINITE_LOOP
**
**step  2 :
**      if "loop" equal to zero meaning the philosopher had enough eaten.
**
** step 3 : if the loop if finish (loop = 0) so stop others threads
*/

void				*cycle_philosopher(void *ptr)
{
	int				loop;
	t_philosopher	*philosopher;

	loop = g_info.limit_nb_meal;
	philosopher = (t_philosopher *)ptr;
	while (loop)
	{
		philosopher_eat(philosopher);
		philosopher_sleep_and_thinking(philosopher);
		if (loop != INFINITE_LOOP)
			loop--;
		usleep(1000);
	}
	g_info.current_number_of_meals = g_info.limit_nb_meal;
	return (0);
}
