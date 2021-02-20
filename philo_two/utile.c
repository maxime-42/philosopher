/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 21:11:48 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/19 21:11:57 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void				detach_all_threads(void)
{
	int				index;

	index = -1;
	while (++index < g_info.nb_philo)
	{
		pthread_detach(g_info.ptr_thread_id[index]);
	}
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
