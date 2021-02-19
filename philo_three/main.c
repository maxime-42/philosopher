/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:34:38 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/19 14:21:21 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	the function "launch_process" does:
**		create one process for each philosopĥe
**		initialize time to eat for each them
**		child process starte with "cycle_philosopher"
**		parent process waiting each child process
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
**fonction "main" does two thing:
**	step one: parser argument
**	step two: launch process
*/

int						main(int nb_arg, char **argument)
{
	int					ret;

	ret = parsing(nb_arg, argument);
	if (ret == ERROR)
		return (ERROR);
	else
	{
		ret = start_process(g_info.nb_philo);
	}
	return (ret);
}
