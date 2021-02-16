/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:34:38 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/16 14:53:21 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include "philo.h"

/*
**	check if the philosophizing eats late
**	if the philosophizing eats late -> exit programe return DIE
*/

static int				join_all_thread(pthread_t thread_id[])
{
	int					id;
	int					ret;

	id = -1;
	while (++id < g_info.nb_philo)
	{
		ret = pthread_join(thread_id[id], NULL);
		if (ret)
		{
			print_error("Error join threads\n");
		}
	}
	return (ret);
}

/*
**	the function launch_thread define two things:
**		1 number threads ie thread_id[nb_philo]
**		2 number philosopher ie  philo[nb_philo];
**	id it is index for each philosopher
*/

static int				launch_threads(t_philosopher *philosopher,
int nb_philo, pthread_t thread_id[])
{
	int					id;
	int					ret;

	id = -1;
	while (++id < nb_philo)
	{
		philosopher[id].time_last_meal = get_actuel_time();
		ret = pthread_create(&thread_id[id], NULL, cycle_philosopher, &philosopher[id]);
		if (ret)
		{
			print_error("Error create thread of philosopher\n");
			return (ERROR);
		}
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
	ret = init_mutex(fork, &end);
	if (ret)
		return (ret);
	g_info.fork = &fork[0];
	g_info.end = &end;
	ret = launch_threads(&philosopher[0], nb_philosopher, thread_id);
	if (ret)
		return (ERROR);
	check_is_alive(philosopher);
	ret = join_all_thread(thread_id);
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