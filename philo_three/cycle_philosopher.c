/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:20:20 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/20 14:15:23 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h>

/*
** this function check if the philosophe eaten in late
** if a philosophe  eaten in later :
** 		kill every process in the process group by kill(0, SIGINT)
**		RTFM : https://man7.org/linux/man-pages/man2/kill.2.html
*/

static void				*check_is_alive(void *ptr)
{
	t_philosopher		*philosopher;
	long				time_actuel;
	long				time_difference;

	philosopher = (t_philosopher *)ptr;
	while (1)
	{
		sem_wait(g_info.write);
		time_actuel = get_actuel_time();
		time_difference = time_actuel - philosopher->time_last_meal;
		if ((time_actuel - philosopher->time_last_meal) >= g_info.time_to_die)
		{
			printf("Dies id %d | time %ld | diff = %ld time_to_die =  %d\n",
			philosopher->id, time_actuel, time_difference, g_info.time_to_die);
			kill(0, SIGINT);
			return (0);
		}
		sem_post(g_info.write);
		usleep(1000);
	}
	return (0);
}

static void				philosopher_eat(t_philosopher *philosopher)
{
	sem_wait(g_info.fork);
	printf("%ld %d has taken a fork\n", get_actuel_time(), philosopher->id);
	printf("%ld %d has taken a fork\n", get_actuel_time(), philosopher->id);
	philosopher->time_last_meal = get_actuel_time();
	printf("%ld %d is eating \n", philosopher->time_last_meal, philosopher->id);
	usleep(g_info.time_to_eat * 1000);
	sem_post(g_info.fork);
}

static void				philosopher_sleep_and_think(t_philosopher *philosopher)
{
	printf("%ld %d is sleeping\n", get_actuel_time(), philosopher->id);
	usleep(g_info.time_to_sleep * 1000);
	printf("%ld %d is thinking\n", get_actuel_time(), philosopher->id);
}

/*
** step 1 : create thread which check process is alive (if it eaten in later)
** step 2 : loop
** 			loop equal to number of meals.
** 			if number some meals is not present it will be infinite loop
** step	3 :
**			if "loop" equal to zero meaning :
**				the philosopher had enough eaten.
**				so this process will kill every others in the process group
**			RTFM : https://man7.org/linux/man-pages/man2/kill.2.html
*/

int						cycle_philosopher(void *ptr)
{
	int					loop;
	t_philosopher		*philosopher;
	pthread_t			thread_id;

	loop = g_info.limit_nb_meal;
	philosopher = (t_philosopher *)ptr;
	pthread_create(&thread_id, NULL, check_is_alive, philosopher);
	while (loop != 0)
	{
		philosopher_eat(philosopher);
		philosopher_sleep_and_think(philosopher);
		usleep(1000);
		if (loop != INFINITE_LOOP)
			loop--;
	}
	sem_wait(g_info.end);
	write(1, "Every one has eaten enought", 28);
	pthread_detach(thread_id);
	kill(0, SIGINT);
	sem_post(g_info.end);
	exit(0);
}
