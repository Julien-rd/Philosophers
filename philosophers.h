/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:08:16 by jromann           #+#    #+#             */
/*   Updated: 2025/09/03 14:44:58 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define EVERYONE_ALIVE 1
# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAILURE 0

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				status;
	int				threads_ready;
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
	t_data			*data;
	pthread_t		newthread;
}					t_philosopher;

typedef struct s_container
{
	t_data			data;
	t_philosopher	*philo;
}					t_container;

int					ft_atoi(const char *nptr);
void				initialise_data(t_data *data, int argc,
						char **argv);
size_t				gettime(t_philosopher *philo);
void				initialise_philos(t_data *data);
void				*routine(void *ptr);
void				optimised_usleep(size_t time, t_philosopher *philo);
void				cleanup(t_philosopher *philo, int flag, char *msg);
int					ready2eat(t_philosopher *philo);

// actions
void				nap(t_philosopher *philo);
void				eat(t_philosopher *philo);
void				think(t_philosopher *philo);

//protected functions
void *protected_malloc(size_t size);
void protected_pthread_create(t_philosopher *philo, int pos);
void protected_pthread_create(t_philosopher *philo, int pos);
void protected_pthread_join(t_philosopher *philo, int pos);
void protected_pthread_mutex_init(pthread_mutex_t	mutex, t_philosopher *philo);
void protected_pthread_mutex_lock(pthread_mutex_t	mutex, t_philosopher *philo);
void protected_pthread_mutex_unlock(pthread_mutex_t	mutex, t_philosopher *philo);

#endif
