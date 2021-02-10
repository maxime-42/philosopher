#include "philo.h"
#include <pthread.h>


void				test(t_philosopher philosopher[], int id_philo) 
{ 
	int				state;
	int				left;
	int				right;
	long			actuel_time;

	left = philosopher[id_philo].left;
	right = philosopher[id_philo].right;
	state = philosopher[id_philo].state;
	if (state == HUNGRY && left != EATING && right != EATING) 
	{ 
		actuel_time = get_actuel_time();
		actuel_time = actuel_time - philosopher[id_philo].time_last_meal;
		if (actuel_time > g_info.time_to_eat)
		{
			printf("philosoher die \n");
			exit(0);
		}
		philosopher[id_philo].state = EATING;
		// sleep(g_info.time_to_sleep);
		printf("Philosopher %d takes fork %d and %d\n", id_philo + 1, left + 1, id_philo + 1);
		printf("Philosopher %d is Eating\n", id_philo + 1); 
		// sem_post(&S[phnum]) has no effect 
		// during takefork 
		// used to wake up hungry philosophers 
		// during putfork 
		// sem_post(&S[phnum]); 
	}
} 

void				take_fork(t_philosopher philosopher, int id_philo) 
{ 
	//   sem_wait(&mutex); 
  
    // state that hungry 
	philosopher.state = HUNGRY;

    printf("Philosopher %d is Hungry\n", id_philo + 1); 
  
    // eat if neighbours are not eating 
    test(philosopher, id_philo); 
  
    // sem_post(&mutex); 
  
    // if unable to eat wait to be signalled 
    // sem_wait(&S[phnum]); 
      sleep(g_info.time_to_sleep); 
}

// void				put_fork(t_philosopher philosopher[], int id_philo)
// {
// 	int left;
// 	int right;

// 	left = philosopher[id_philo].left;
// 	right = philosopher[id_philo].right;
// 	// sem_wait(&mutex); 

// 	// state that thinking 
// 	philosopher[id_philo].state = THINKING; 

// 	printf("Philosopher %d putting fork %d and %d down\n", id_philo + 1, left + 1, id_philo + 1); 
// 	printf("Philosopher %d is thinking\n", id_philo + 1); 
// 	test(philosopher, left); 
// 	test(philosopher, right); 
// 	// sem_post(&mutex); 
// }

void				*philosopher(void *ptr)
{
	int				loop;
	t_philosopher	*philo;

	philo =(t_philosopher *)ptr;
	loop = g_info.nb_meal;
	while (loop)
	{
		philo->state = THINKING;
		printf("%ld %d is thinking \n", get_actuel_time(), philo->id);
		// printf("time [%ld] | id_philosopher [%d] | is thinking \n", get_actuel_time(), *id);
		philo->state = EATING;
		philo->time_last_meal = get_actuel_time();
		printf("%ld %d is eating \n", get_actuel_time(), philo->id);
		usleep(g_info.time_to_eat * 1000);
		philo->state = NAP;
		printf("%ld %d is napping \n", get_actuel_time(), philo->id);
		usleep(g_info.time_to_sleep * 1000);
		if (loop != INFINITE_LOOP)
			loop--;
	}
	(void)ptr;
	return (0);
}

// void				*philosopher_2(void *num)
// {
// 	int				*id;
// 	int				loop;

// 	id = num;
// 	loop = g_info.nb_meal;
// 	while (loop)
// 	{
// 		sleep(1);
// 		// take_fork(g_info.philosopher, *id); 
// 		// sleep(g_info.time_to_sleep);
// 		// put_fork(philosopher, *id);
// 		// printf("philo number [%d]\n", *id);
// 		printf("philo number [%d]\n", *id);

// 		if (loop != INFINITE_LOOP)
// 			loop--;
// 	}
// 	(void)id;
// 	return (0);
// }