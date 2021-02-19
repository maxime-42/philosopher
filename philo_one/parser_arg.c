/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 19:38:18 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/19 19:32:07 by lenox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

/*
** get_arg does:
**		step 1 : got the argument in struct g_info
**		step 2 : check if numbe of meals is present
**				if is not present the program will be an infini loop
**		step 3 : check if the arguments given respect the subject line:35 to 38
*/

static int		get_arg(char **arg)
{
	int			t_sleep;

	g_info.nb_philo = ft_atoi(arg[1]);
	g_info.time_to_die = ft_atoi(arg[2]);
	g_info.time_to_eat = ft_atoi(arg[3]);
	g_info.time_to_sleep = ft_atoi(arg[4]);
	if (arg[5])
		g_info.limit_nb_meal = ft_atoi(arg[5]);
	else
		g_info.limit_nb_meal = INFINITE_LOOP;
	if (g_info.nb_philo < 2)
		return (ERROR);
	t_sleep = g_info.time_to_sleep;
	if (g_info.time_to_die <= 0 || g_info.time_to_eat <= 0 || t_sleep <= 0)
		return (ERROR);
	return (SUCCESS);
}

/*
** check if syntaxe of argument programme
** if number argument is less 5 or greater than 6 it is error
** if a argument is not a digit character it is error
*/

static int		check_arg(int nb_arg, char **arg)
{
	int			ret;
	int			index;

	index = 0;
	if (nb_arg < 5 || nb_arg > 6)
	{
		ret = print_error("Bad number argument\n");
		return (ret);
	}
	while (arg[++index])
	{
		ret = str_is_digit(arg[index]);
		if (ret == ERROR)
		{
			print_error("Argument is not digit character\n");
			return (ERROR);
		}
	}
	return (ret);
}

/*
**	parsing does:
**		step 1 : initialize global structure g_info with zero
**		step 2 : check the arguments which given to program
**		step 3 : if step 1 passe in success then we can get
**				 the argument inside the struct g_info
*/

int				parsing(int nb_arg, char **arg)
{
	int			ret;

	memset(&g_info, 0, sizeof(t_info));
	ret = check_arg(nb_arg, arg);
	if (ret == ERROR)
		return (ERROR);
	ret = get_arg(arg);
	if (ret == ERROR)
	{
		print_error("Error argument\n");
	}
	return (ret);
}
