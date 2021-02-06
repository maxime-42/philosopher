#include "philo.h"

int main(int nb_arg, char **arg)
{
    int ret;
    ret = parsing(nb_arg, arg);
    if (ret == ERROR)
        return (ERROR);
    printf("hellow\n");
    printf("g_info.nb_philo %d\n", g_info.nb_philo);
    printf("g_info.time_to_die %d\n", g_info.time_to_die);
    printf("g_info.time_to_eat %d\n", g_info.time_to_eat);
    printf("g_info.time_to_sleep %d\n", g_info.time_to_sleep);

    return (SUCCESS);
}