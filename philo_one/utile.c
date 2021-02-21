/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:46:56 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/21 13:36:59 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int					clear_mutex(pthread_mutex_t fork[])
{
	int				ret;
	int				id;

	id = -1;
	while (++id < g_info.nb_philo)
	{
		ret = pthread_mutex_destroy(&fork[id]);
	}
	ret = pthread_mutex_destroy(&g_info.end);
	ret = pthread_mutex_destroy(&g_info.general);
	return (ret);
}

long				get_actuel_time(void)
{
	long			ret;
	struct timeval	t1;

	ret = 0;
	gettimeofday(&t1, NULL);
	ret = t1.tv_sec * 1000;
	ret += t1.tv_usec / 1000;
	return (ret);
}
