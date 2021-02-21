/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:30:25 by mkayumba          #+#    #+#             */
/*   Updated: 2021/02/21 12:18:00 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <pthread.h>
# include <stdio.h>
# define ERROR -1
# define IS_NOT_DIGIT -1
# define SUCCESS 0
# define INFINITE_LOOP -1
# define DIE 4

typedef	struct		s_philosopher
{
	long			time_last_meal;
	int				id;
	int				nb_meal;
	long			t_start;
	long			t_now;
	int				pid;
	pthread_t		thread;
}					t_philosopher;

typedef	struct		s_info
{
	int				count;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_philosopher	*philosopher;
	int				limit_nb_meal;
	sem_t			*fork;
	sem_t			*write;
	sem_t			*end;

}					t_info;

t_info				g_info;

int					print_error(char *msg);
int					ft_atoi(const char *nptr);
int					str_is_digit(char *str);
int					parsing(int nb_arg, char **arg);
long				get_actuel_time(void);
int					cycle_philosopher(void *ptr);
void				init_philosopher(t_philosopher philo[], int nb_philo);
void				init_semaphor(t_info *info);
void				clear_semaphor(t_info *info);
#endif
