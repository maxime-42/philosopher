/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:16:32 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/19 18:06:55 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void					init_philosopher(t_philosopher philo[], int nb_philo)
{
	int					id;

	id = -1;
	while (++id < nb_philo)
	{
		memset(&philo[id], 0, sizeof(t_philosopher));
		philo[id].id = id + 1;
		philo[id].right = id;
		philo[id].left = (id + 1) % g_info.nb_philo;
	}
}

int						init_mutex(pthread_mutex_t fork[], pthread_mutex_t *end)
{
	int					id;
	int					ret;

	id = -1;
	while (++id < g_info.nb_philo)
	{
		if ((ret = pthread_mutex_init(&fork[id], NULL)))
		{
			print_error("error init mutex\n");
			return (ERROR);
		}
	}
	ret = pthread_mutex_init(end, NULL);
	ret = pthread_mutex_init(&g_info.general, NULL);
	if (ret)
	{
		print_error("error init mutex\n");
		ret = ERROR;
	}
	return (ret);
}

int						clear_mutex(pthread_mutex_t fork[], pthread_mutex_t end)
{
	int					ret;
	int					id;

	id = -1;
	while (++id < g_info.nb_philo)
	{
		ret = pthread_mutex_destroy(&fork[id]);
		if (ret)
		{
			print_error("error closet mutex\n");
		}
	}
	ret = pthread_mutex_destroy(&end);
	ret = pthread_mutex_destroy(&g_info.general);
	if (ret)
	{
		print_error("error init mutex\n");
		ret = ERROR;
	}
	return (ret);
}