#include "philo.h"
#include <stdio.h>
/*
** this function initialize g_info
** get argument of programme
*/
static int		get_arg(char **arg)
{ 
	g_info.nb_philo = ft_atoi(arg[1]);
	g_info.time_to_die = ft_atoi(arg[2]);
	g_info.time_to_eat = ft_atoi(arg[3]);
	g_info.time_to_sleep = ft_atoi(arg[4]);
	if (arg[5])
		g_info.nb_meal = ft_atoi(arg[5]);
	else
		g_info.nb_meal = INFINITE_LOOP;
	if (g_info.nb_philo < 2)
		return (ERROR);
	if (g_info.time_to_die <= 0 || g_info.time_to_eat <= 0 || g_info.time_to_sleep <= 0)
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

int				parsing(int nb_arg, char **arg)
{
	int			ret;

	ret = check_arg(nb_arg, arg);
	if (ret == ERROR)
	return (ERROR);
	g_info.current_number_of_meals = 0;
	ret = get_arg(arg);
	return (ret);
}