/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:34:38 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/18 17:14:50 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"




/*
**	check if the philosophizing eats late
**	if the philosophizing eats late -> exit programe return DIE
*/

/*
**	the function launch_thread define two things:
**		1 number threads ie thread_id[nb_philo]
**		2 number philosopher ie  philo[nb_philo];
**	id it is index for each philosopher
*/

static int				launch_process(t_philosopher *philosopher)
{
	int					id;
	int					status;
	pid_t				pid;


	id = -1;
	while (++id < g_info.nb_philo)
	{
		philosopher[id].time_last_meal = get_actuel_time();
		if ((pid = fork()) < 0)
		{
			print_error("error on fork");
			return (ERROR);
		}
		else if (!pid)
			(void)cycle_philosopher(&philosopher[id]);
	}
	if (pid > 0)
		waitpid(-1, &status, 0);
	write(1, "Every one has eaten enought", 28);
	kill(0, SIGINT);
	return (SUCCESS);
}

static int				start_process(int nb_philosopher)
{
	int					ret;
	t_philosopher		philosopher[nb_philosopher];

	ret = 0;
	init_philosopher(philosopher, nb_philosopher);
	init_semaphor(&g_info);
	ret = launch_process(&philosopher[0]);
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
		g_count = 0;
		ret = start_process(g_info.nb_philo);
	}
	return (ret);
}