/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:09:27 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/19 16:18:08 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** this function convert time in millisecond
*/

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
