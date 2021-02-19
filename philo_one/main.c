/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:34:38 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/19 18:05:15 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include "philo.h"


/*
**	the function launch_thread define two things:
**		1 number threads ie thread_id[nb_philo]
**		2 number philosopher ie  philo[nb_philo];
**	id it is index for each philosopher
*/

static int				launch_threads(t_philosopher *philosopher, pthread_t thread_id[], int id)
{
	int					ret;

	while (id < g_info.nb_philo)
	{
		philosopher[id].time_last_meal = get_actuel_time();
		ret = pthread_create(&thread_id[id], NULL, cycle_philosopher, &philosopher[id]);
		if (ret)
		{
			print_error("Error create thread of philosopher\n");
			return (ERROR);
		}
		id++;
		id++;
	}
	return (ret);
}

static int				start_thread(int nb_philosopher)
{
	int					ret;
	t_philosopher		philosopher[nb_philosopher];
	pthread_t			thread_id[nb_philosopher];
	pthread_mutex_t		fork[nb_philosopher];
	pthread_mutex_t		end;

	g_info.fork = fork;
	init_philosopher(philosopher, nb_philosopher);
	if ((ret = init_mutex(fork, &end)))
		return (ret);
	g_info.fork = &fork[0];
	g_info.end = &end;
	g_info.ptr_thread_id = &thread_id[0];
	ret = launch_threads(&philosopher[0], thread_id, 0);
	usleep(1000);
	ret = launch_threads(&philosopher[0], thread_id, 1);
	if (ret)
		return (ERROR);
	ret = check_is_alive(philosopher);
	if (ret != DIE)
		clear_mutex(fork, end);
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