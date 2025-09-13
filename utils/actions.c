/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:45:41 by jromann           #+#    #+#             */
/*   Updated: 2025/09/13 16:20:09 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printaction(char *str, t_philosopher *philo)
{
	protected_pthread_mutex_lock(&philo->data->main_mutex, philo);
	printf("%zu %d %s\n", gettime(philo), philo->id, str);
	protected_pthread_mutex_unlock(&philo->data->main_mutex, philo);
}

void	optimised_usleep(size_t time, t_philosopher *philo)
{
	size_t	end;
	int		remaining;

	if (time == 0)
		return ;
	remaining = 1;
	end = gettime(philo) + time;
	while (remaining > 0)
	{
		remaining = end - gettime(philo);
		if (remaining > 1000)
			usleep((remaining * 1000) / 2);
	}
}
int	ready2eat(t_philosopher *philo)
{
	if (philo->right_fork == 1 && philo->left_fork == 1)
		return (1);
	return (0);
}

void	eat(t_philosopher *philo)
{
	// if (philo->id % 2 == 0)
	// 	pickup_fork(philo, RIGHT_FORK);
	// else
	// 	pickup_fork(philo, LEFT_FORK);
	protected_pthread_mutex_lock(&philo->data->forks[philo->id - 1], NULL);
	printaction("has taken a fork", philo);
	protected_pthread_mutex_lock(&philo->data->forks[philo->id
			% philo->data->number_of_philosophers], NULL);
	printaction("has taken a fork", philo);
	printaction("is eating", philo);
	optimised_usleep(philo->data->time_to_eat, philo);
	philo->last_eaten = gettime(philo);
	philo->eaten_meals += 1;
	philo->right_fork = 0;
	philo->left_fork = 0;
	philo->time_alive = 0;
	protected_pthread_mutex_unlock(&philo->data->forks[philo->id
		% philo->data->number_of_philosophers], NULL);
	protected_pthread_mutex_unlock(&philo->data->forks[philo->id - 1], NULL);
	philo->ready = NOTREADY;
}

void	nap(t_philosopher *philo)
{
	printaction("is sleeping", philo);
	optimised_usleep(philo->data->time_to_sleep, philo);
}

void	think(t_philosopher *philo)
{
	printaction("is thinking", philo);
}