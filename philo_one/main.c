#include "philo.h"
#include <pthread.h> 

static void         init_philo(t_philosopher philo[], int nb_philo)
{
    int             id;

    id = -1;
    while (++id < nb_philo)
    {
		philo[id].id = id;
		philo[id].meals = 0;
		philo[id].right = id;
		philo[id].left = (id + 1) % nb_philo;
    }
}

void                launch_thread(int nb_philo)
{
    t_philosopher   philo[nb_philo];
    pthread_t       thread_id[nb_philo]; 
    int             id;

    id = -1;
    init_philo(philo, nb_philo);
    g_info.philosopher = &philo;
    while (++id < nb_philo)
    { 
        pthread_create(&thread_id[id], NULL, philosopher, &philo[id]); 
    }
    id = -1;
    while (++id < nb_philo) 
        pthread_join(thread_id[id], NULL);
}

int                 main(int nb_arg, char **arg)
{
    int             ret;

    ret = parsing(nb_arg, arg);
    if (ret == ERROR)
        return (ERROR);
    launch_thread(g_info.nb_philo);
    printf("hellow\n");
    printf("g_info.nb_philo %d\n", g_info.nb_philo);
    printf("g_info.time_to_die %d\n", g_info.time_to_die);
    printf("g_info.time_to_eat %d\n", g_info.time_to_eat);
    printf("g_info.time_to_sleep %d\n", g_info.time_to_sleep);
    return (SUCCESS);
}