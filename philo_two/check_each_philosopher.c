#include "philo.h"

/*
*	check if the philosophizing eats late
*	if the philosophizing eats late -> exit programe return DIE
*/
int				check_time_meals_(t_philosopher philosopher)
{
	long		time_actuel;
	long		time_difference;

	time_actuel = get_actuel_time();
	time_difference = time_actuel - philosopher.time_last_meal;
	if (time_difference > g_info.time_to_eat)
	{
		printf("%ld %d is id dead \n", time_difference, philosopher.id);
		return (DIE);
	}
	return (0);
}

// int				check_nb_meals(t_philosopher philosopher)
// {
// 	if (g_info.nb_meal != INFINITE_LOOP)
// 	{
// 		if (philosopher.)
// 		g_info.current_number_of_meals++;
// 	}
// 	if ()
// }