/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:20:20 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/19 17:53:57 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <semaphore.h>


/*
**	tihis check two things:
**		1-if all philosophizing them all have eaten enough
**		2-if a philosopher has to eat late so he dies.
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
	else if ((time_actuel - philosopher.time_last_meal) >= g_info.time_to_die)
	{
		printf("philo id %d | time %ld | dif_time = %ld t_die =  %d\n",
		philosopher.id, time_actuel, time_difference, g_info.time_to_die);
		return (DIE);
	}
	return (0);
}

/*
** this function travel each philosophe one by one
** checks the state of each of them
*/

int						check_is_alive(t_philosopher philosopher[])
{
	int					id;
	int					ret;

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
	int				right;
	int				left;
	
	right = philosopher->right;
	left = philosopher->left;
	pthread_mutex_lock(&g_info.fork[right]);
	printf("%ld %d has taken a fork\n", get_actuel_time(), philosopher->id);
	pthread_mutex_lock(&g_info.fork[left]);
	printf("%ld %d has taken a fork\n", get_actuel_time(), philosopher->id);
	pthread_mutex_lock(g_info.end);
	printf("%ld %d is eating \n", philosopher->time_last_meal, philosopher->id);
	philosopher->time_last_meal = get_actuel_time();
	pthread_mutex_unlock(g_info.end);
	usleep(g_info.time_to_eat * 1000);
	pthread_mutex_unlock(&g_info.fork[right]);
	pthread_mutex_unlock(&g_info.fork[left]);
}

static void			philosopher_sleep(t_philosopher *philosopher) 
{
	printf("%ld %d is sleeping\n",get_actuel_time(), philosopher->id);
	usleep(g_info.time_to_sleep * 1000);
	printf("%ld %d is thinking\n",get_actuel_time(), philosopher->id);

}

void				detach_all_threads(void)
{
	int				index;

	index = -1;
	while (++index < g_info.nb_philo)
	{
		pthread_detach(g_info.ptr_thread_id[index]);
	}
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
		if (loop != INFINITE_LOOP)
			loop--;
	}
	(void)philosopher;
	g_info.current_number_of_meals = g_info.limit_nb_meal;
	pthread_mutex_lock(&g_info.general);
	detach_all_threads();
	pthread_mutex_unlock(&g_info.general);
	return (0);
}