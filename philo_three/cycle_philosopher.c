/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:20:20 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/19 11:11:19 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h>
/*
** this function check if the philosophe eaten in late
** if the philosophe  eaten in later -> kill every process in the process group by kill(0, SIGINT)
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
			printf("Dies some philosophe id %d | time %ld | difference_time = %ld time_to_die =  %d\n",philosopher->id, time_actuel, time_difference, g_info.time_to_die);
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

	printf("%ld %d is taken a fork\n", get_actuel_time(), philosopher->id);
	printf("%ld %d is taken a fork\n", get_actuel_time(), philosopher->id);
	philosopher->time_last_meal = get_actuel_time();
	printf("%ld %d is eating \n", philosopher->time_last_meal, philosopher->id);
	sem_wait(g_info.end);
	sem_post(g_info.end);
	usleep(g_info.time_to_eat * 1000);
	sem_post(g_info.fork);
}


static void				philosopher_sleep_and_think(t_philosopher *philosopher)
{
	printf("%ld %d is sleeping\n",get_actuel_time(), philosopher->id);
	usleep(g_info.time_to_sleep * 1000);
	printf("%ld %d is thinking\n", get_actuel_time(), philosopher->id);
}


int						cycle_philosopher(void *ptr)
{
	int					loop;
	t_philosopher		*philosopher;
 	pthread_t			thread_id;

	loop = g_info.limit_nb_meal;
	philosopher = (t_philosopher *)ptr;
	// philosopher->time_last_meal = get_actuel_time();
 	pthread_create(&thread_id, NULL, check_is_alive, philosopher);
	while (loop != 0)
	{
		philosopher_eat(philosopher);
		philosopher_sleep_and_think(philosopher);
		usleep(1000);
		if (loop != INFINITE_LOOP)
			loop--;
	}
	kill(0, SIGINT);
	pthread_detach(thread_id);
	exit (0);
}