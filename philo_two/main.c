#include "philo.h"
#include <pthread.h> 
#include <stdio.h> 

static void					init_philo(t_philosopher philo[], int nb_philo)
{
	int						id;

	id = -1;
	while (++id < nb_philo)
	{
		philo[id].id = id;
		philo[id].time_last_meal = 0;
		philo[id].right = id;
		philo[id].nb_meal = 0;
		philo[id].left = (id + 1) % nb_philo;
	}
}

void					check_is_alive(t_philosopher philosopher[])
{
	int					id;

	while (1)
	{
		id = -1;
		while (++id < g_info.philosopher)
		{
		}
		usleep(1000);
	}
}
/*
*	launch allow define : 
*		1 number threads ie thread_id[nb_philo] 
*		2 numer philosopher ie  philo[nb_philo];
*	id it is index for each philosopher
*/
static void				launch_thread(int nb_philo)
{
	t_philosopher		philo[nb_philo];
	pthread_t			thread_id[nb_philo]; 
	int					id;

	id = -1;
	init_philo(philo, nb_philo);
	while (++id < nb_philo)
	{
		philo[id].id = id;
		philo[id].time_last_meal = get_actuel_time();
		pthread_create(&thread_id[id], NULL, philosopher, &philo[id]); 
	}
	id = -1;
	while (++id < nb_philo)
	{
		if (pthread_join(thread_id[id], NULL))
		{
			printf("Error joining thread\n");
			return (ERROR);
		}
	}
}
/*
*fonction main do two thing:
*	step one: parser argument
*	step two: launch thread
*/
int						main(int nb_arg, char **arg)
{
	int					ret;

	ret = parsing(nb_arg, arg);
	if (ret == ERROR)
		return (ERROR);
	else
	{
		launch_thread(g_info.nb_philo);
	}
	return (SUCCESS);
}