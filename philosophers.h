/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:08:16 by jromann           #+#    #+#             */
/*   Updated: 2025/10/10 15:57:11 by jromann          ###   ########.fr       */
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

# define ACTIVE 1
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
	size_t			philo_amount;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			required_meals;
	size_t			philos_done;
	size_t			start_time;
	size_t			open_threads;
	bool			status;
	bool			threads_ready;
	bool			function_fail;
	pthread_mutex_t	main_mutex;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philosopher
{
	size_t			id;
	bool			right_fork;
	bool			left_fork;
	bool			life;
	bool			ready;
	size_t			time_alive;
	size_t			last_eaten;
	size_t			eaten_meals;
	t_data			*data;
	pthread_t		newthread;
}					t_philosopher;

// main
int					initialise_data(t_data *data, int argc, char **argv);
int					start_simulation(t_data *data);

// simulation_helpers
int					cleanup(t_philosopher *philo, t_data *data, int flag,
						char *msg);
size_t				gettime(t_philosopher *philo);
void				*routine(void *ptr);
void				optimised_usleep(size_t time, t_philosopher *philo);
void				pickup_fork(t_philosopher *philo, int flag);
int					ready2eat(t_philosopher *philo);
int					alive_check(t_philosopher *philo);

// actions
void				nap(t_philosopher *philo);
void				eat(t_philosopher *philo);
void				think(t_philosopher *philo);
void				printaction(char *str, t_philosopher *philo);

// protected functions
int					protected_pthread_create(t_philosopher *philo, int pos);

// helper
int					print_num(int n);
size_t				ft_strlen(char *str);
int					ft_atoi(const char *nptr, bool *overflow);

#endif
