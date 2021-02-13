/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:20:20 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/13 23:50:29 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <semaphore.h>

/*
*	this attibute count 'philosopher->nb_meal' count number meal of philosopher
*	each philosophizing counter has its own number of meals
*/
static void			counte_the_number_of_meals(t_philosopher *philosopher)
{ 
	if (philosopher->nb_meal != REACHED_NUMBER_OF_MEALS_LIMIT)
	{
		g_info.current_number_of_meals++;
		if (philosopher->nb_meal == g_info.limit_nb_meal)
		{
			philosopher->nb_meal = REACHED_NUMBER_OF_MEALS_LIMIT;
		}
	}
}

static void			philosopher_eat(t_philosopher *philosopher) 
{ 
	sem_wait(g_info.fork);
	printf("%ld %d is taken a fork\n", get_actuel_time(), philosopher->id);
	philosopher->state = EATING;
	philosopher->time_last_meal = get_actuel_time();
	printf("%ld %d is eating \n", philosopher->time_last_meal, philosopher->id);
	sem_wait(g_info.end);
	counte_the_number_of_meals(philosopher);
	sem_post(g_info.end);
	usleep(g_info.time_to_eat * 1000);
	sem_post(g_info.fork);
	(void)philosopher;
}

/*
*	this function allow to try to take fork
*	if the fork is unable philosopher will wait 
*/
static void			philosopher_sleep(t_philosopher *philosopher) 
{
	printf("%ld %d is sleeping\n",get_actuel_time(), philosopher->id);
	usleep(g_info.time_to_sleep);
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
		philosopher_sleep(philosopher);
		usleep(100);
		if (loop != INFINITE_LOOP)
			loop--;
	}
	(void)philosopher;
	return (0);
}

// void				*philosopher(void *ptr)
// {
// 	int				loop;
// 	t_philosopher	*philo;

// 	philo =(t_philosopher *)ptr;
// 	loop = g_info.nb_meal;
// 	while (loop)
// 	{

// 		// printf("time [%ld] | id_philosopher [%d] | is thinking \n", get_actuel_time(), *id);
// 		// philo->state = EATING;
// 		// philo->time_last_meal = get_actuel_time();
// 		// printf("%ld %d is eating \n", get_actuel_time(), philo->id);
// 		// usleep(g_info.time_to_eat * 1000);
// 		// philo->state = NAP;
// 		// printf("%ld %d is napping \n", get_actuel_time(), philo->id);
// 		usleep(g_info.time_to_sleep * 1000);
// 		if (loop != INFINITE_LOOP)
// 			loop--;
// 	}
// 	(void)ptr;
// 	return (0);
// }