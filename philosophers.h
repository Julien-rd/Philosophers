/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:08:16 by jromann           #+#    #+#             */
/*   Updated: 2025/10/10 13:53:54 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define EVERYONE_ALIVE 1
# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAILURE 0
# define RIGHT_FORK 0
# define LEFT_FORK 1
# define DEAD 0
# define ALIVE 1
# define NOTREADY 0
# define READY 1

typedef struct s_data
{
	int				philo_amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				required_meals;
	int				status;
	int				threads_ready;
	int				philos_done;
	size_t			start_time;
	pthread_mutex_t	main_mutex;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philosopher
{
	int				id;
	int				right_fork;
	int				left_fork;
	int				life;
	int				ready;
	int				time_alive;
	int				last_eaten[1];
	int				eaten_meals;
	t_data			*data;
	pthread_t		newthread;
}					t_philosopher;

int					initialise_data(t_data *data, int argc, char **argv);
int					initialise_philos(t_data *data);
int					cleanup(t_philosopher *philo, t_data *data, int flag,
						char *msg);
size_t				gettime(t_philosopher *philo);
void				*routine(void *ptr);
void				optimised_usleep(size_t time, t_philosopher *philo);
void				pickup_fork(t_philosopher *philo, int flag);
int					ready2eat(t_philosopher *philo);
void				alive_check(t_philosopher *philo);

// actions
void				nap(t_philosopher *philo);
void				eat(t_philosopher *philo);
void				think(t_philosopher *philo);
void				printaction(char *str, t_philosopher *philo);

// protected functions
int					protected_pthread_create(t_philosopher *philo, t_data *data,
						int pos);
int					protected_pthread_mutex_init(pthread_mutex_t *mutex);

// helper
void				print_num(int n);
size_t				ft_strlen(char *str);
int					ft_atoi(const char *nptr, bool *overflow);

#endif
