/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:34:38 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/20 13:21:52 by mkayumba         ###   ########.fr       */
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

static int		launch_threads(t_philosopher *philo, pthread_t t_id[], int id)
{
	int			ret;

	while (id < g_info.nb_philo)
	{
		philo[id].time_last_meal = get_actuel_time();
		ret = pthread_create(&t_id[id], NULL, cycle_philosopher, &philo[id]);
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

/*
** step 1 : initialize each philosophe
**
** step 2 : to don't start every threads at the same time :
**		start threads odd launch_threads(&philosopher[0], thread_id, 0)
**		start threads even launch_threads(&philosopher[0], thread_id, 1)
** step 3:
**		check life of each philosopher by  this "check_is_alive(philosopher)"
**		this function "check_is_alive" is like a phread
*/

static int		start_thread(int nb_philosopher)
{
	int					ret;
	t_philosopher		philosopher[nb_philosopher];
	pthread_t			thread_id[nb_philosopher];
	pthread_mutex_t		fork[nb_philosopher];

	g_info.fork = fork;
	init_philosopher(philosopher, nb_philosopher);
	if ((ret = init_mutex(fork)))
		return (ret);
	g_info.fork = &fork[0];
	g_info.ptr_thread_id = &thread_id[0];
	ret = launch_threads(&philosopher[0], thread_id, 0);
	usleep(1000);
	ret = launch_threads(&philosopher[0], thread_id, 1);
	if (ret)
		return (ERROR);
	ret = check_is_alive(philosopher);
	clear_mutex(fork);
	return (ret);
}

/*
**fonction main does two thing:
**	step 1: parser argument
**	step 2: launch thread
*/

int				main(int nb_arg, char **argument)
{
	int			ret;

	ret = parsing(nb_arg, argument);
	if (ret == ERROR)
		return (ERROR);
	else
	{
		ret = start_thread(g_info.nb_philo);
		system("leaks philo_one");

	}
	return (ret);
}
