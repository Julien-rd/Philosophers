/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:08:16 by jromann           #+#    #+#             */
/*   Updated: 2025/09/12 16:34:07 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// typedef enum
// {
// 	RIGHT_FORK;
// 	LEFT_FORK;
// 	DEAD;
// 	ALIVE;
// } t_opcode;

# define EVERYONE_ALIVE 1
# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAILURE 0
# define RIGHT_FORK 0
# define LEFT_FORK 1
# define DEAD 0
# define ALIVE 1

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				status;
	int				threads_ready;
	int				philos_done;
	size_t			start_time;
	pthread_mutex_t	main_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philosopher
{
	int				id;
	int				right_fork;
	int				left_fork;
	int				life;
	int				time_alive;
	int				last_eaten;
	int				eaten_meals;
	t_data			*data;
	pthread_t		newthread;
}					t_philosopher;

int					ft_atoi(const char *nptr);
int					initialise_data(t_data *data, int argc, char **argv);
int					initialise_philos(t_data *data);
int					cleanup(t_philosopher *philo, int flag, char *msg);
size_t				gettime(t_philosopher *philo);
void				*routine(void *ptr);
void				optimised_usleep(size_t time, t_philosopher *philo);
void				pickup_fork(t_philosopher *philo, int flag);
int					ready2eat(t_philosopher *philo);
void				alive_check(t_philosopher *philo, int action);

// actions
void				nap(t_philosopher *philo);
void				eat(t_philosopher *philo);
void				think(t_philosopher *philo);
void				printaction(char *str, t_philosopher *philo);

// protected functions
void				*protected_malloc(size_t size);
int					protected_pthread_create(t_philosopher *philo, int pos);
int					protected_pthread_create(t_philosopher *philo, int pos);
int					protected_pthread_join(t_philosopher *philo, int pos);
int					protected_pthread_mutex_init(pthread_mutex_t *mutex,
						t_philosopher *philo);
int					protected_pthread_mutex_lock(pthread_mutex_t *mutex,
						t_philosopher *philo);
int					protected_pthread_mutex_unlock(pthread_mutex_t *mutex,
						t_philosopher *philo);

#endif
