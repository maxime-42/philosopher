/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:34:38 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/20 14:00:49 by mkayumba         ###   ########.fr       */
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

static int				launch_threads(t_philosopher *philosopher,
int nb_philo, pthread_t thread_id[])
{
	int					id;
	int					ret;

	id = -1;
	while (++id < nb_philo)
	{
		philosopher[id].time_last_meal = get_actuel_time();
		ret = pthread_create(&thread_id[id], NULL,
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
	pthread_t			thread_id[nb_philosopher];

	init_philosopher(philosopher, nb_philosopher);
	init_semaphor(&g_info);
	g_info.ptr_thread_id = &thread_id[0];
	ret = launch_threads(&philosopher[0], nb_philosopher, thread_id);
	if (ret)
		return (ERROR);
	ret = check_is_alive(philosopher);
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
		system("leaks philo_two");
	}
	return (ret);
}
