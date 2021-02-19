/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:20:20 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/19 21:40:09 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <semaphore.h>

/*
*	check if the philosophizing eats late
*	if the philosophizing eats late -> exit programe return DIE
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
	if ((time_actuel - philosopher.time_last_meal) >= g_info.time_to_die)
	{
		printf("Die id %d | time %ld | dif = %ld time_to_die =  %d\n", 
		philosopher.id, time_actuel, time_difference, g_info.time_to_die);
		return (DIE);
	}
	return (0);
}


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
*	this function allow to try to take fork
*	if the fork is unable philosopher will wait 
*/
static void			philosopher_sleep_and_thinking(t_philosopher *philosopher) 
{
	printf("%ld %d is sleeping\n",get_actuel_time(), philosopher->id);
	usleep(g_info.time_to_sleep * 1000);
	printf("%ld %d is thinking\n", get_actuel_time(), philosopher->id);

}

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
	sem_wait(g_info.write);
	g_info.current_number_of_meals = g_info.limit_nb_meal;
	detach_all_threads();
	sem_post(g_info.write);
	return (0);
}