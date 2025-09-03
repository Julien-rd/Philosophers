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

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				status;
	size_t			start_time;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philosopher
{
	int				id;
	int				right_fork;
	int				left_fork;
	int				life;
	pthread_t		newthread;
}					t_philosopher;

typedef struct s_container
{
	t_data			data;
	t_philosopher	*philo;
}					t_container;

int					ft_atoi(const char *nptr);
void				initialise_data(t_container *container, int argc,
						char **argv);
size_t				gettime(t_container *container);
void				initialise_philos(t_container *container);
void				*routine(void *ptr);
void				nap(t_container *container);
void				eat(t_container *container);
void				think(t_container *container);
void				optimised_usleep(size_t time, t_container *container);

#endif
