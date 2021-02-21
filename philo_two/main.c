/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:34:38 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/21 16:12:09 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include "philo.h"

/*
** this function is only called when one philosophe dead
** a philosophe dies when it had eaten in late
** the purpose is to terminates all thread
*/

static void				detach_all_threads(t_philosopher philosopher[])
{
	int					id;

	id = -1;
	while (++id < g_info.nb_philo)
	{
		pthread_detach(philosopher[id].thread);
	}
	id = g_info.philo_dead;
	printf("Die id %d | time %ld | dif_time = %ld time_die =  %d\n",
	id, g_info.time_actuel, g_info.time_difference, g_info.time_to_die);
}

/*
** the purpose of this function:
** 		is to terminate all threads after one philosopher had eaten
**
** this function is called when one philosophe finished to ate
** waits for the thread specified by "philosopher[id].thread" to terminate
*/

static void				join_all_thread(t_philosopher philosopher[])
{
	int					id;
	int					ret;

	id = -1;
	while (++id < g_info.nb_philo)
	{
		ret = pthread_join(philosopher[id].thread, NULL);
		if (ret)
			print_error("Failed to join thread\n");
	}
	printf("Every one has eaten enought\n");
}

/*
**	the function launch_thread define two things:
**		1 number threads ie thread_id[nb_philo]
**		2 number philosopher ie  philo[nb_philo];
**	id it is index for each philosopher
*/

static int				launch_threads(t_philosopher *philosopher)
{
	int					id;
	int					ret;

	id = -1;
	while (++id < g_info.nb_philo)
	{
		philosopher[id].time_last_meal = get_actuel_time();
		ret = pthread_create(&philosopher[id].thread, NULL,
		cycle_philosopher, &philosopher[id]);
		if (ret)
		{
			print_error("Error create thread of philosopher\n");
			return (ERROR);
		}
	}
	return (ret);
}

/*
** step 1 : initialize each philosophe
**
** step 2 : initialize semaphor for each philosopher
**
** step 3 : launch threads
**
** this function "check_is_alive" :
**		is like a phread wich check life some philosophers
*/

static int				start_thread(int nb_philosopher)
{
	int					ret;
	t_philosopher		philosopher[nb_philosopher];

	init_philosopher(philosopher, nb_philosopher);
	init_semaphor(&g_info);
	ret = launch_threads(&philosopher[0]);
	if (ret)
		return (ERROR);
	ret = check_is_alive(philosopher);
	if (ret == EVERY_ONE_HAS_EAT_ENOUGHT)
		join_all_thread(philosopher);
	else if (ret == DIE)
		detach_all_threads(philosopher);
	clear_semaphor(&g_info);
	return (ret);
}

/*
**fonction main do two thing:
**	step one: parser argument
**	step two: launch thread
*/

int						main(int nb_arg, char **argument)
{
	int					ret;

	ret = parsing(nb_arg, argument);
	if (ret == ERROR)
		return (ERROR);
	else
	{
		ret = start_thread(g_info.nb_philo);
	}
	return (ret);
}
