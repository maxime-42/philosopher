/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:11:32 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/19 13:28:47 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	classic function libc RTFM : https://linux.die.net/man/3/strlen
*/

static int			ft_strlen(char *str)
{
	int				index;

	index = 0;
	while (str[index])
	{
		index++;
	}
	return (index);
}

/*
** check if a character is a digit character
** if "c" is between 0 and 9 return 0 otherwise return 0
** RTFM : https://linux.die.net/man/3/isdigit
*/

static int			ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

/*
**	print the message error in the Standard error
** 	RTFM https://en.wikipedia.org/wiki/File_descriptor
*/

int					print_error(char *msg)
{
	int				nb_bytes;

	nb_bytes = ft_strlen(msg);
	write(2, msg, nb_bytes);
	return (ERROR);
}

/*
** check if a string (str) is composed by
** only digit character otherwise it is error
*/

int					str_is_digit(char *str)
{
	int				index;
	int				ret;

	index = -1;
	while (str[++index])
	{
		ret = ft_isdigit(str[index]);
		if (ret == 0)
			return (ERROR);
	}
	return (SUCCESS);
}

/*
** classic function libc atoi  RTFM : https://linux.die.net/man/3/atoi
** ovf = overflow, to check overflow
*/

int					ft_atoi(const char *nptr)
{
	long			n;
	int				s;
	int				ovf;

	n = 0;
	s = 1;
	ovf = 1;
	while ((*nptr && *nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if ((*nptr && *nptr == '-') || *nptr == '+')
	{
		if (*nptr == '-')
			s *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9' && ovf == 1)
	{
		n = (n * 10) + *nptr++ - 48;
		if (n < 0 && s == 1)
			ovf = -1;
		else if (n < 0 && s == -1)
			ovf = 0;
	}
	return (ovf == 1 ? n * s : ovf);
}
