#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>
# define ERROR -1
# define IS_NOT_DIGIT -1
# define SUCCESS 0
# define INFINITE_LOOP -1
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 

typedef	struct		s_philosopher
{
	int             meals;
	int				id;
	long		    t_start;
	long		    t_now;
	int				state;
	pthread_t	    thread;
	int			    right;
	int			    left;
}					t_philosopher;

typedef	struct		s_info
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_philosopher	*philosopher;
	int				nb_meal;
}					t_info;


t_info              g_info;

int					print_error(char *msg);
int					ft_atoi(const char *nptr);
int     			str_is_digit(char *str);
int     			parsing(int nb_arg, char **arg);
void        		*philosopher(void *num);
long				get_actuel_time(void);

#endif